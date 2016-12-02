// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "UnrealNetwork.h"
#include "BaseCharacter.h"

ABaseCharacter::ABaseCharacter()
{
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

void ABaseCharacter::GetLifetimeReplicatedProps(TArray < FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseCharacter, isAttacking);
	DOREPLIFETIME(ABaseCharacter, _Life);
}

void ABaseCharacter::SetLife(int Life)
{
	_Life = Life;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Life = %d"), _Life));
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
	this->SetIsAttacking(true);
}

void ABaseCharacter::ReceiveDamage(int dmg)
{
	this->_Life -= dmg;
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

	for (int i = 0; i < results.Num(); ++i)
	{
		FOverlapResult hit = results[i];
		if (hit.Actor->GetClass()->IsChildOf(ABaseCharacter::StaticClass()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, hit.Actor->GetName());

			if (hit.Actor != this)
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
	SetIsAttacking(false);
	return true;
}

void ABaseCharacter::Death()
{
	this->SetActorEnableCollision(false);
}

void ABaseCharacter::Move()
{
	
}