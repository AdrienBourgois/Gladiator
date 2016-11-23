// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "AICharacter.h"
#include "AIControl.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CurrentPlayer = nullptr;
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

void AAICharacter::Init(AActor* Player, float safeDist)
{
	SafeDistance = safeDist;
	CurrentPlayer = Player;
	AAIControl*	AIController = Cast<AAIControl>(GetController());
	UBlackboardComponent* BlackBoard = AIController->FindComponentByClass<UBlackboardComponent>();
	BlackBoard->SetValueAsObject("Player", CurrentPlayer);
	BlackBoard->SetValueAsBool("GotoPlayer", false);
}

void AAICharacter::CalcVectorSafeDistance()
{
	FVector Difference = CurrentPlayer->GetActorLocation() - GetActorLocation();
	float CurDistance; FVector Direction;
	Difference.ToDirectionAndLength(Direction, CurDistance);
	float TargetDistance = CurDistance - SafeDistance;
	FVector FSafeDistance = GetActorLocation() + Direction * TargetDistance;

	AAIControl*	AIController = Cast<AAIControl>(GetController());
	UBlackboardComponent* BlackBoard = AIController->FindComponentByClass<UBlackboardComponent>();
	BlackBoard->SetValueAsVector("SafeDist", FSafeDistance);
}
