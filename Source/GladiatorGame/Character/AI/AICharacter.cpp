// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "AICharacter.h"
#include "AIControl.h"
#include "AIDirector.h"
#include "BehaviorTree/BehaviorTreeComponent.h"


AAICharacter::AAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentPlayer = nullptr;
	AIManager = nullptr;
	BlackBoard = nullptr;
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAICharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	LookAt();
}

void AAICharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AAICharacter::Init(AAIDirector* AImgr, AActor* Player, float safeDist, float distIA)
{
	AIManager = AImgr;
	SafeDistance = safeDist;
	DistanceWithIA = distIA;
	CurrentPlayer = Player;
	AAIControl*	AIController = Cast<AAIControl>(GetController());
	BlackBoard = AIController->FindComponentByClass<UBlackboardComponent>();
	SetState(StateAI::GoSafe);
	BlackBoard->SetValueAsObject("Player", CurrentPlayer);
	BlackBoard->SetValueAsObject("Weapon", nullptr);
	BlackBoard->SetValueAsObject("Weapon", nullptr);
}

void AAICharacter::CalcVectorSafeDistance()
{
	if (AIManager == nullptr || CurrentPlayer == nullptr || BlackBoard == nullptr)
		return;

	TArray<AAICharacter*> AIList = AIManager->GetAIList();
	FVector FSafeDistance = CalcVector(GetActorLocation(), CurrentPlayer->GetActorLocation(), SafeDistance);
	FSafeDistance.Z = GetActorLocation().Z;
	for (int idx = 0; idx < AIList.Num(); idx++)
	{
		if ((AIList[idx] != this) && (DistanceToTarget(FSafeDistance, AIList[idx]->GetSafeLocation()) < DistanceWithIA))
		{
			FSafeDistance = CalcVector(FSafeDistance, AIList[idx]->GetSafeLocation(), DistanceWithIA);
			FSafeDistance.Z = GetActorLocation().Z;
		}
	}
	
	FSafeDistanceInBoard = FSafeDistance;
	BlackBoard->SetValueAsVector("SafeDist", FSafeDistanceInBoard);
}

FVector AAICharacter::CalcVector(FVector MyLocation, FVector target, float SafeDist)
{
	FVector Difference = target - MyLocation;
	float CurDistance; FVector Direction;
	Difference.ToDirectionAndLength(Direction, CurDistance);
	float TargetDistance = CurDistance - SafeDist;

	return MyLocation + Direction * TargetDistance;
}

float AAICharacter::DistanceToTarget(FVector Pos , FVector target)
{
	FVector Difference = target - Pos;
	float CurDistance; FVector Direction;
	Difference.ToDirectionAndLength(Direction, CurDistance);
	return CurDistance;
}

void AAICharacter::MoveTo(FVector Target)
{
	FVector Difference = Target - GetActorLocation();
	float CurDistance;
	FVector Direction;
	Difference.ToDirectionAndLength(Direction, CurDistance);
	float MoveDistance = FMath::Clamp(CurDistance, -50.0f * GetWorld()->DeltaTimeSeconds, -50.0f * GetWorld()->DeltaTimeSeconds);
	SetActorLocation(GetActorLocation() + Direction * MoveDistance);
}

void AAICharacter::LookAt()
{
	if (CurrentPlayer == nullptr)
		return;
	FRotator TargetRotation = (CurrentPlayer->GetActorLocation() - GetActorLocation()).Rotation();
	TargetRotation.Pitch = 0.0f;

	FRotator SmoothRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->DeltaTimeSeconds, RotateSpeed);
	SetActorRotation(SmoothRotation);
}

void AAICharacter::ReceiveDamage(int dmg)
{
	Super::ReceiveDamage(dmg);
	
	CheckStuff();
}

void AAICharacter::CheckStuff()
{
	if (!equipment[shieldRef])
	{
		UE_LOG(LogTemp, Warning, TEXT("Shield False"));
		SetState(StateAI::ShieldLost);
		BlackBoard->SetValueAsObject("Shield", AIManager->GoToWeapon(shieldRef));
	}
	else if (!equipment[weaponRef])
	{
		UE_LOG(LogTemp, Warning, TEXT("weapon False"));
		SetState(StateAI::WeaponLost);
		BlackBoard->SetValueAsObject("Weapon", AIManager->GoToWeapon(weaponRef));
	}
	else if (equipment[shieldRef] && equipment[weaponRef])
	{
		UE_LOG(LogTemp, Warning, TEXT("stuff TRUE"));
		SetState(StateAI::GoSafe);
	}
}

bool AAICharacter::AttackEnd()
{
	if (AIManager == nullptr)
		return false;

	this->isAttacking = false;
	if (State == StateAI::GoToPlayer)
		SetState(StateAI::GoSafe);
	return true;
}

void AAICharacter::TryPickEquipment()
{
	Super::TryPickEquipment();
	CheckStuff();
}

void AAICharacter::Death()
{
	this->SetActorEnableCollision(false);

	AAIControl*	AIController = Cast<AAIControl>(GetController());
	AIController->BrainComponent->StopLogic("");

	CurrentPlayer = nullptr;

	if (AIManager != nullptr)
		AIManager->DeathAI(this);
}