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
	FVector CalcVector(FVector MyLocation, FVector target, float SafeDist);
	float DistanceToTarget(FVector Pos, FVector target);

	void MoveTo(FVector Target);
	void LookAt();
	virtual void ReceiveDamage(int dmg = 1) override;
	virtual bool AttackEnd() override;
	virtual void TryPickEquipment();
	virtual void Death() override;

	void SetGoToPlayer(bool value) const {BlackBoard->SetValueAsBool("GotoPlayer", value);}
	void SetShieldLost(bool value) const {BlackBoard->SetValueAsBool("ShieldLost", value); }
	void SetWeaponLost(bool value) const {BlackBoard->SetValueAsBool("WeaponLost", value); }
	FVector GetSafeLocation() const { return FSafeDistanceInBoard; }

	UPROPERTY(EditAnywhere)
		float RotateSpeed = 20.0f;

private:
	AActor* CurrentPlayer;
	FVector FSafeDistanceInBoard;
	float SafeDistance;
	float DistanceWithIA;
	UBlackboardComponent* BlackBoard;

	AAIDirector* AIManager;
};
