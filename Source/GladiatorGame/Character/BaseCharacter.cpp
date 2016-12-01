// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "UnrealNetwork.h"
#include "BaseCharacter.h"

ABaseCharacter::ABaseCharacter()
{
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