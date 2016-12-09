// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "UnrealNetwork.h"
#include "Animation/SkeletalMeshActor.h"
#include "BaseCharacter.h"


ABaseCharacter::ABaseCharacter()
{
	this->InitEquipmentMap();
	SetLife(5);
	bReplicates = true;
}
ABaseCharacter::ABaseCharacter(int Life)
{
	SetLife(Life);
	bReplicates = true;
}
ABaseCharacter::~ABaseCharacter()
{
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	this->InitEquipmentMap();
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray < FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCharacter, isAttacking);
	DOREPLIFETIME(ABaseCharacter, _Life);
}

void ABaseCharacter::SetLife(int Life)
{
	_Life = Life;
	if (Role < ROLE_Authority)
	{
		ServSetLife(Life);
	}
}

void ABaseCharacter::ServSetLife_Implementation(int Life)
{
	SetLife(Life);
}

bool ABaseCharacter::ServSetLife_Validate(int Life)
{
	return true;
}

void ABaseCharacter::SetIsAttacking(bool bNewSomeBool)
{
	isAttacking = bNewSomeBool;
	if (Role < ROLE_Authority)
	{
		ServSetIsAttacking(bNewSomeBool);
	}
}

void ABaseCharacter::ServSetIsAttacking_Implementation(bool bNewSomeBool)
{
	SetIsAttacking(bNewSomeBool);
}

bool ABaseCharacter::ServSetIsAttacking_Validate(bool bNewSomeBool)
{
	return true;
}

void ABaseCharacter::Attack()
{
	if (this->weaponRef)
		if (this->equipment[weaponRef] != nullptr)
			return;

	this->SetIsAttacking(true);
}

void ABaseCharacter::ReceiveDamage(int dmg)
{
	float multiplier = 1.f;

	if (this->shieldRef)
		if (this->equipment[shieldRef] != nullptr)
			multiplier = 2.f;

	this->_Life -= dmg * multiplier;

	//_LifeBar->ActionWidget_Implementation(dmg);
	//ULifeBar* converted = Cast<ULifeBar>(LifeBar);
	//if (converted)
	//	converted->ActionWidget_Implementation(dmg);

	this->RandomDrop();
	if (this->_Life <= 0)
		this->Death();
}

bool ABaseCharacter::HammerHit()
{
	if (Role < ROLE_Authority)
		return true;
	TArray<FOverlapResult> results;
	this->GetWorld()->OverlapMultiByChannel(results,
		this->GetActorLocation() + this->GetActorForwardVector() * ONE_METER,
		this->GetActorRotation().Quaternion(),
		ECollisionChannel::ECC_MAX,
		FCollisionShape::MakeSphere(ONE_METER*.5f));

	for (int i = 0; i < results.Num(); ++i)
	{
		FOverlapResult hit = results[i];
		if (hit.Actor->GetClass()->IsChildOf(ABaseCharacter::StaticClass()))
		{
			if (hit.Actor != this)
			{
				ABaseCharacter* enemy = Cast<ABaseCharacter>(hit.GetActor());
				if (enemy != nullptr && enemy != this)
					enemy->ReceiveDamage();
			}
		}
	}
	return true;
}

bool ABaseCharacter::AttackEnd()
{
	SetIsAttacking(false);
	return true;
}

void ABaseCharacter::Death()
{
	SetLife(_Life);
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
			USkeletalMeshComponent* skeletal_mesh_component = Cast<USkeletalMeshComponent>(converted);
			if (skeletal_mesh_component)
			{
				if (skeletal_mesh_component->SkeletalMesh == weaponMeshRef)
					weaponRef = converted;
				if (skeletal_mesh_component->SkeletalMesh == shieldMeshRef)
					shieldRef = converted;
			}
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
		{
			USceneComponent* collider = Cast<USceneComponent>(equipment[key]->GetComponentByClass(UBoxComponent::StaticClass()));
			if (collider)
				if (FVector::Dist(collider->GetComponentLocation(), this->GetActorLocation()) <= this->pickRadius)
					PickEquipment(equipment[key]);
		}
}


void ABaseCharacter::PickEquipment(AActor* picked)
{
	TArray<USceneComponent*> keys = TArray<USceneComponent*>(); equipment.GetKeys(keys);
	
	for (USceneComponent* key : keys)
		if (equipment[key] == picked)
		{
			equipment[key] = nullptr;
			key->SetVisibility(true);
		}

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
	boxcomp->SetHiddenInGame(true);
	
	pop_actor->SetActorLocation(base->GetComponentLocation());
	boxcomp->SetWorldTransform(base->GetComponentTransform());

	FVector dropdir = this->GetActorUpVector() * 1.5f - this->GetActorForwardVector();
	FVector dropRot = -GetActorRightVector()* FMath::FRandRange(100.f, 300.f) + GetActorUpVector() * FMath::FRandRange(-300.f, 300.f);

	dropdir = dropdir.RotateAngleAxis(FMath::FRandRange(-10.f, 10.f), this->GetActorUpVector());
	dropdir = dropdir.RotateAngleAxis(FMath::FRandRange(0.f, 45.f), this->GetActorRightVector());

	boxcomp->SetPhysicsAngularVelocity(dropRot);
	boxcomp->SetPhysicsLinearVelocity(dropdir * 300.f);

	base->SetVisibility(false);

	pop_actor->SetReplicates(true);
	pop_actor->SetReplicateMovement(true);

	return pop_actor;
}
