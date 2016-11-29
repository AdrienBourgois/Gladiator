// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "AIDirector.h"
#include "GladiatorGameState.h"


AAIDirector::AAIDirector()
{
	PrimaryActorTick.bCanEverTick = true;
	IAClass = nullptr;
	CurrentPlayer = nullptr;

}

void AAIDirector::BeginPlay()
{
	Super::BeginPlay();
	
	if (IAClass == nullptr)
		return;
	CurrentPlayer = Cast<AActor>(UGameplayStatics::GetPlayerPawn(this, 0));

	AIList.SetNum(NbEnemy);
	for (size_t i = 0; i < NbEnemy; ++i)
	{
		FVector SpawnLocation = SpawnPointsList[i]->GetActorLocation();
		AIList[i] = Cast<AAICharacter>(GetWorld()->SpawnActor(IAClass, &SpawnLocation, &FRotator::ZeroRotator));
		AIList[i]->SpawnDefaultController();
		AIList[i]->Init(this, CurrentPlayer, DistanceSafe, DistanceToOtherAI);
	}
	ChoiceGoToPlayer();
}

void AAIDirector::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AAIDirector::ChoiceGoToPlayer()
{
	if (AIList.Num() <= 0)
		return;

	for (int i = 0; i < AIList.Num(); ++i)
	{
		
		AIList[i]->SetGoToPlayer(false);
	}

	int idx = FMath::RandRange(0, AIList.Num()-1);
	AIList[idx]->SetGoToPlayer(true);
}

void AAIDirector::DeathAI(AAICharacter* Target)
{
	AIList.Remove(Target);
	if (AIList.Num() <= 0)
	{
		Cast<AGladiatorGameState>(GetWorld()->GetGameState())->PlayerWin();
	}

	ChoiceGoToPlayer();
}