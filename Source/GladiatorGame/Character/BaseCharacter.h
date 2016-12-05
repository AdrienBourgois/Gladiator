// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"
/**
 * 
 */

const float ONE_METER = 100.f;

UCLASS(Blueprintable)
class GLADIATORGAME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	ABaseCharacter();
	ABaseCharacter(int Life);
	virtual ~ABaseCharacter();
	
	virtual void BeginPlay();

	virtual void Attack();
	virtual void ReceiveDamage(int dmg = 1);
	virtual void Death();
	virtual void Move();

	UFUNCTION(BlueprintCallable, Category = "Character Attack") virtual bool HammerHit();
	UFUNCTION(BlueprintCallable, Category = "Character Attack") virtual bool AttackEnd();

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int _Life = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool isAttacking = false;

	UPROPERTY(EditAnywhere) float dropRate = .5f;
	UPROPERTY(EditAnywhere) float pickRadius = 100.f;

	TMap<USceneComponent*, AActor*> equipment = TMap<USceneComponent*, AActor*>();

	void InitEquipmentMap();

	void RandomDrop();
	
	void TryPickEquipment();
	void PickEquipment(AActor* picked);

	AActor* DropEquipment(USceneComponent* toDrop);
	AActor* PopActorFromComponent(USkeletalMeshComponent* base);
};
