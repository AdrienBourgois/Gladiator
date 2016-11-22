// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Character/BaseCharacter.h"
#include "CharacterPlayer.generated.h"

UCLASS()
class GLADIATORGAME_API ACharacterPlayer : public ACharacter, public BaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterPlayer();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

private:

#pragma region Members

	UCameraComponent* camera = nullptr;

	float speed = 250.f;

	float sensitivity = 100.f;
	float len = 100.f;
	float minLen = 100.f;



#pragma endregion 

	// --- ----- --- //

#pragma region Functions

	void SetupInputs();
	UCameraComponent* FindCamera();

	void VerticalAxis(float value);
	void HorizontalAxis(float value);

	void VerticalMovement(float value);
	void HorizontalMovement(float value);

	void Attack();

	bool IsTargetViewable();
	bool IsTargetInRange();

	void AdaptView();
	void AdaptFromCollision(FVector collider);
	void CheckDistance();

#pragma endregion

};
