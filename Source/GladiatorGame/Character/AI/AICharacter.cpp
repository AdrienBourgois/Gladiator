// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "AICharacter.h"
#include "AIControl.h"
#include "AIDirector.h"


// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CurrentPlayer = nullptr;
	AIManager = nullptr;
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAICharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
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
	BlackBoard->SetValueAsObject("Player", CurrentPlayer);
	BlackBoard->SetValueAsBool("GotoPlayer", false);
}

void AAICharacter::CalcVectorSafeDistance()
{
	if (AIManager == nullptr || CurrentPlayer == nullptr)
		return;

	TArray<AAICharacter*> AIList = AIManager->GetAIList();
	FVector FSafeDistance = CalcVector(CurrentPlayer, SafeDistance);
	FSafeDistance.Z = GetActorLocation().Z;
	for (int idx = 0; idx < AIList.Num(); idx++ )
		if (AIList[idx] != this)
			if (DistanceToTarget(FSafeDistance, AIList[idx]) < DistanceWithIA)
			{
				FVector FDistForIA = CalcVector(AIList[idx], DistanceWithIA);

				FSafeDistance += FDistForIA;
				FSafeDistance.Z = GetActorLocation().Z;
			}
	
	
	BlackBoard->SetValueAsVector("SafeDist", FSafeDistance);
}

FVector AAICharacter::CalcVector(AActor* target, float SafeDist)
{
	FVector Difference = target->GetActorLocation() - GetActorLocation();
	float CurDistance; FVector Direction;
	Difference.ToDirectionAndLength(Direction, CurDistance);
	float TargetDistance = CurDistance - SafeDist;
	return GetActorLocation() + Direction * TargetDistance;
}

float AAICharacter::DistanceToTarget(FVector Pos ,AActor* target)
{
	FVector Difference = target->GetActorLocation() - Pos;
	float CurDistance; FVector Direction;
	Difference.ToDirectionAndLength(Direction, CurDistance);
	return CurDistance;
}

void AAICharacter::LookAt()
{
	
}