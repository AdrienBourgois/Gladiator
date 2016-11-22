// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Camera.generated.h"

UCLASS()
class GLADIATORGAME_API ACamera : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACamera();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SetupInputs();

	void VerticalAxis(float value);
	void HorizontalAxis(float value);

	bool IsTargetViewable();
	void AdaptView();
	void AdaptFromCollision(FVector collider);
	void CheckDistance();

private:

	UCameraComponent* FindCamera();

	UCameraComponent* camera = nullptr;

	float sensitivity = 100.f;
	float len = 100.f;
	float minLen = 100.f;
};
