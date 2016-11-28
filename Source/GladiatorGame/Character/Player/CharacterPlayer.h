// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Character/BaseCharacter.h"
#include "CharacterPlayer.generated.h"

const int LFACTOR = -1;
const int RFACTOR = 1;

UCLASS()
class GLADIATORGAME_API ACharacterPlayer :  public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterPlayer();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	bool AttackEnd() override;

private:

#pragma region Members

	TArray<AActor*> enemy_array = TArray<AActor*>();
	TMap<float, AActor*> enemy_map = TMap<float, AActor*>();
	AActor* lockTarget = nullptr;

	UPROPERTY(EditAnywhere) float speed = 250.f;

	UPROPERTY(EditAnywhere) UCameraComponent* cameraComponent = nullptr;
	UPROPERTY(EditAnywhere) float sensitivity = 100.f;
	UPROPERTY(EditAnywhere) float minLen = 100.f;
	float len = 0.f;

#pragma endregion 

	// --- ----- --- //

#pragma region Functions

	// ----- //

#pragma region Inputs

	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	void SetupInputs();

	void VerticalAxis(float value);
	void HorizontalAxis(float value);

	void VerticalMovement(float value);
	void HorizontalMovement(float value);

#pragma endregion 

	// ----- //

#pragma region Camera Control

	bool IsTargetViewable();
	bool IsTargetInRange();

	void AdaptView();
	void AdaptFromCollision(FVector collider);
	void CheckDistance();

	UCameraComponent* FindCamera();

#pragma endregion

	// ----- //

#pragma region LockSystem

	void CallLock();

	void DebugLock(AActor* target = nullptr);

	TArray<AActor*> UpdateEnemyList();
	void SortEnemyList();
	float GetActorPositionFactor(AActor* factorized);

	AActor* FindForwardTarget();
	AActor* FindNearestEnemyFrom(FVector pos);

	void SwitchTarget(/*float value*/);


#pragma endregion
	
	// ----- //

#pragma region Utilities

	static float GetAngleBetween(FVector V1, FVector V2);
	static int GetLRFactor(AActor* ref_actor, AActor* tested_actor);

#pragma endregion

	// --- ----- --- //

#pragma endregion

};
