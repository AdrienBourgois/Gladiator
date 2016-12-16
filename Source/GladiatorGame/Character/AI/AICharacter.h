// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Character/BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AICharacter.generated.h"

UENUM(BlueprintType)
enum class StateAI : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	GoToPlayer	UMETA(DisplayName = "GoToPlayer"),
	GoSafe		UMETA(DisplayName = "GoSafe"),
	WeaponLost	UMETA(DisplayName = "WeaponLost"),
	ShieldLost	UMETA(DisplayName = "ShieldLost")
};

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
	void CheckStuff();
	virtual void ReceiveDamage(int dmg = 1) override;
	virtual bool AttackEnd() override;
	virtual void TryPickEquipment() override;
	virtual void Death() override;

	StateAI GetState() { return State; }
	void SetState(StateAI value) { State = value;  BlackBoard->SetValueAsEnum("State", uint8(State)); }
	FVector GetSafeLocation() const { return FSafeDistanceInBoard; }

	UPROPERTY(EditAnywhere)
		float RotateSpeed = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		StateAI State;

private:
	AActor* CurrentPlayer;
	FVector FSafeDistanceInBoard;
	float SafeDistance;
	float DistanceWithIA;
	UBlackboardComponent* BlackBoard;

	AAIDirector* AIManager;

};
