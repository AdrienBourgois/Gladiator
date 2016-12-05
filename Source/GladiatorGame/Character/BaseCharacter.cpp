// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "BaseCharacter.h"
#include "Animation/SkeletalMeshActor.h"

ABaseCharacter::ABaseCharacter()
{
	this->InitEquipmentMap();
}
ABaseCharacter::ABaseCharacter(int Life)
{
	_Life = Life;
}
ABaseCharacter::~ABaseCharacter()
{
}

void ABaseCharacter::Attack()
{
	this->isAttacking = true;
}

void ABaseCharacter::ReceiveDamage(int dmg)
{
	this->_Life -= dmg;
	this->RandomDrop();
	if (this->_Life <= 0)
		this->Death();
}

bool ABaseCharacter::HammerHit()
{
	TArray<FOverlapResult> results;
	this->GetWorld()->OverlapMultiByChannel(results,
		this->GetActorLocation() + this->GetActorForwardVector() * ONE_METER,
		this->GetActorRotation().Quaternion(),
		ECollisionChannel::ECC_MAX,
		FCollisionShape::MakeSphere(ONE_METER*.5f));

	//DrawDebugSphere(GetWorld(), this->GetActorLocation() + this->GetActorForwardVector() * ONE_METER, ONE_METER*.5f, 32, FColor::Blue, false, 2.f);

	for (int i = 0; i < results.Num(); ++i)
	{
		FOverlapResult hit = results[i];
		if (hit.Actor->GetClass()->IsChildOf(ABaseCharacter::StaticClass()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, hit.Actor->GetName());

			if (hit.Actor->GetClass() != this->GetClass())
			{
				ABaseCharacter* enemy = Cast<ABaseCharacter>(hit.GetActor());
				if (enemy != nullptr)
					enemy->ReceiveDamage();
			}
		}

	}
	return true;
}

bool ABaseCharacter::AttackEnd()
{
	this->isAttacking = false;
	return true;
}

void ABaseCharacter::Death()
{
	this->SetActorEnableCollision(false);
}

void ABaseCharacter::Move()
{

}

void ABaseCharacter::InitEquipmentMap()
{
	FMath::Clamp<float>(dropRate, 0.f, 1.f);

	TArray<UActorComponent*> component_list = TArray<UActorComponent*>();
	this->GetComponents(component_list);

	for (UActorComponent* component : component_list)
	{
		USceneComponent* converted = Cast<USceneComponent>(component);
		if (!converted)
			continue;
		else
		{
			if (converted->HasAnySockets() && converted->GetAttachSocketName() != "None")
				equipment.Add(converted, nullptr);
		}
	}
}

void ABaseCharacter::RandomDrop()
{
	float rand = FMath::FRandRange(0.f, 1.f);
	if (rand > dropRate || equipment.Num() == 0)
		return;
	else
	{
		TArray<USceneComponent*> keys = TArray<USceneComponent*>(); equipment.GetKeys(keys);

		int dropidx = FMath::RandRange(0, equipment.Num() - 1);
		if (equipment[keys[dropidx]] == nullptr)
			equipment[keys[dropidx]] = DropEquipment(keys[dropidx]);
	}
}

void ABaseCharacter::TryPickEquipment()
{
	TArray<USceneComponent*> keys = TArray<USceneComponent*>(); equipment.GetKeys(keys);

	for (USceneComponent* key : keys)
		if (equipment[key] != nullptr)
			if (FVector::Dist(equipment[key]->GetActorLocation(), this->GetActorLocation()) <= this->pickRadius)
				PickEquipment(equipment[key]);
}

void ABaseCharacter::PickEquipment(AActor* picked)
{
	TArray<USceneComponent*> keys = TArray<USceneComponent*>(); equipment.GetKeys(keys);
	
	for (USceneComponent* key : keys)
		if (equipment[key] == picked)
			equipment[key] = nullptr;

	picked->Destroy();
}

AActor* ABaseCharacter::DropEquipment(USceneComponent* toDrop)
{
	USkeletalMeshComponent* converted = Cast<USkeletalMeshComponent>(toDrop);
	if (converted)
		return PopActorFromComponent(converted);

	return nullptr;
}

AActor* ABaseCharacter::PopActorFromComponent(USkeletalMeshComponent* base)
{
	AActor* pop_actor = GetWorld()->SpawnActor<ASkeletalMeshActor>(this->GetActorLocation() + base->GetComponentLocation(), base->GetComponentRotation());

	UPrimitiveComponent* boxcomp = NewObject<UPrimitiveComponent>(pop_actor->GetRootComponent(), UBoxComponent::StaticClass());
	USkeletalMeshComponent* meshcomp = Cast<USkeletalMeshComponent>(NewObject<UPrimitiveComponent>(boxcomp, USkeletalMeshComponent::StaticClass()));

	meshcomp->SetSkeletalMesh(base->SkeletalMesh);

	meshcomp->RegisterComponent();
	meshcomp->Activate();

	boxcomp->RegisterComponent();
	boxcomp->Activate();

	meshcomp->SnapTo(boxcomp);

	Cast<UBoxComponent>(boxcomp)->SetBoxExtent(base->SkeletalMesh->GetImportedBounds().BoxExtent * .5f);
	Cast<UBoxComponent>(boxcomp)->SetCollisionProfileName(TEXT("Droppable"));
	meshcomp->SetCollisionProfileName(TEXT("Droppable"));

	boxcomp->SetSimulatePhysics(true);
	boxcomp->SetHiddenInGame(false);
	
	pop_actor->SetActorLocation(base->GetComponentLocation());
	boxcomp->SetWorldTransform(base->GetComponentTransform());

	FVector dropdir = this->GetActorUpVector() * 1.5f - this->GetActorForwardVector();
	FVector dropRot = -GetActorRightVector()* FMath::FRandRange(100.f, 300.f) + GetActorUpVector() * FMath::FRandRange(-300.f, 300.f);

	dropdir = dropdir.RotateAngleAxis(FMath::FRandRange(-10.f, 10.f), this->GetActorUpVector());
	dropdir = dropdir.RotateAngleAxis(FMath::FRandRange(0.f, 45.f), this->GetActorRightVector());

	boxcomp->SetPhysicsAngularVelocity(dropRot);
	boxcomp->SetPhysicsLinearVelocity(dropdir * 300.f);

	base->SetVisibility(false);

	return pop_actor;
}
