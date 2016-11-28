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
	BlackBoard = nullptr;
	
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
	LookAt();
	//CalcVectorSafeDistance();
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
	_Life = 3;
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

	UE_LOG(LogTemp, Warning, TEXT("Direction x = %f // y = %f // z = %f"), Direction.X, Direction.Y, Direction.Z);
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

	//float TargetDistance = CurDistance - Distance;
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