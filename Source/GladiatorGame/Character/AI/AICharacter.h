// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Character/BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AICharacter.generated.h"

UCLASS()
class GLADIATORGAME_API AAICharacter : public ACharacter, public BaseCharacter
{
	GENERATED_BODY()

public:
	AAICharacter();
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void Init(AActor* Player, float safeDist);
	void CalcVectorSafeDistance();
	
	void SetGoToPlayer(bool value);

private:
	AActor* CurrentPlayer;
	float SafeDistance;
	UBlackboardComponent* BlackBoard;
};
