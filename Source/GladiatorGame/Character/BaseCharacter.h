// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"
/**
 * 
 */
UCLASS(Blueprintable)
class GLADIATORGAME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	ABaseCharacter();
	ABaseCharacter(int Life);
	virtual ~ABaseCharacter();
	
	virtual void Attack();
	virtual void ReceiveDamage(int dmg = 1);
	virtual void Death();
	virtual void Move();

	UFUNCTION(BlueprintCallable, Category = "Character Attack") virtual bool HammerHit();
	UFUNCTION(BlueprintCallable, Category = "Character Attack") virtual bool AttackEnd();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int _Life = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool isAttacking = false;

};
