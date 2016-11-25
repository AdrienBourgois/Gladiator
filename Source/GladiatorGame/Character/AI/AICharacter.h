// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Character/BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AICharacter.generated.h"


class AAIDirector;
UCLASS()
class GLADIATORGAME_API AAICharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AAICharacter();
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void Init(AAIDirector* AImgr, AActor* Player, float safeDist, float distIA);
	void CalcVectorSafeDistance();
	FVector CalcVector(AActor* target, float SafeDist);
	float DistanceToTarget(FVector Pos, AActor* target);

	void LookAt();

	void SetGoToPlayer(bool value) {BlackBoard->SetValueAsBool("GotoPlayer", value);}
	
private:
	AActor* CurrentPlayer;
	float SafeDistance;
	float DistanceWithIA;
	UBlackboardComponent* BlackBoard;

	AAIDirector* AIManager;
};
