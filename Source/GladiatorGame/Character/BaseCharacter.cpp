// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "UnrealNetwork.h"
#include "Animation/SkeletalMeshActor.h"
#include "Character/Equipment/Droppable.h"
#include "BaseCharacter.h"
#include "Kismet/KismetStringLibrary.h"


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

	// --- ----- --- //

#pragma region Network

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

#pragma endregion

	// --- ----- --- //

#pragma region Basics

void ABaseCharacter::Attack()
{
	if (this->weaponRef)
		if (!this->equipment[weaponRef])
			return;

	this->SetIsAttacking(true);
}

void ABaseCharacter::ReceiveDamage(int dmg)
{
	float multiplier = 1.f;

	if (this->shieldRef)
		if (!this->equipment[shieldRef])
			multiplier = 2.f;

	this->_Life -= dmg * multiplier;

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

#pragma endregion

	// --- ----- --- //

#pragma region Equipment Drop

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
				equipment.Add(converted, true);
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

		if (equipment[keys[dropidx]])
			DropEquipment(keys[dropidx]);
	}
}

void ABaseCharacter::TryPickEquipment()
{
	TArray<USceneComponent*> keys = TArray<USceneComponent*>(); equipment.GetKeys(keys);

	TArray<FOverlapResult> results;
	this->GetWorld()->OverlapMultiByChannel(results,
		this->GetActorLocation(),
		this->GetActorRotation().Quaternion(),
		ECollisionChannel::ECC_MAX,
		FCollisionShape::MakeCapsule(pickRadius, this->GetComponentsBoundingBox().GetExtent().Z));

	TArray<AActor*> found = TArray<AActor*>();

	for (USceneComponent* key : keys)
	{
		if (equipment[key])
			continue;

		for (int i = 0; i < results.Num(); ++i)
		{
			FOverlapResult hit = results[i];

			if (hit.GetActor()->GetClass()->IsChildOf(ADroppable::StaticClass()))
			{
				ADroppable* drop = Cast<ADroppable>(hit.GetActor());
				USkeletalMeshComponent* keycast = Cast<USkeletalMeshComponent>(key);
				if (keycast)
					if (drop->IsSameAs(Cast<USkeletalMeshComponent>(key)))
					{
						equipment[key] = true;
						key->SetVisibility(true);
						found.Add(hit.GetActor());
						break;
					}
			}
		}
	}
		for (AActor* cur : found)
			cur->Destroy();
}

void ABaseCharacter::PickEquipment(AActor* picked)
{
	picked->Destroy();
}

AActor* ABaseCharacter::DropEquipment(USceneComponent* toDrop)
{
	USkeletalMeshComponent* converted = Cast<USkeletalMeshComponent>(toDrop);
	if (converted)
	{
		ADroppable* drop = Cast<ADroppable>(GetWorld()->SpawnActor<ADroppable>(converted->GetComponentLocation(), converted->GetComponentRotation()));
		drop->Init(converted);

		FVector force = this->GetActorUpVector() * 1.5f - this->GetActorForwardVector();
		FVector torque = -GetActorRightVector()* FMath::FRandRange(100.f, 300.f) + GetActorUpVector() * FMath::FRandRange(-300.f, 300.f);

		force = force.RotateAngleAxis(FMath::FRandRange(-10.f, 10.f), this->GetActorUpVector());
		force = force.RotateAngleAxis(FMath::FRandRange(0.f, 45.f), this->GetActorRightVector());

		drop->ApplyForces(force * ONE_METER * 3.f, torque);

		equipment[toDrop] = false;
		return Cast<AActor>(drop);
	}
	return nullptr;
	
}

#pragma endregion