// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "AIDirector.h"


AAIDirector::AAIDirector()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AAIDirector::BeginPlay()
{
	Super::BeginPlay();
	
	if (IAClass == nullptr)
		return;
	CurrentPlayer = Cast<AActor>(UGameplayStatics::GetPlayerPawn(this, 0));

	AIList.SetNum(SpawnPointsList.Num());
	for (size_t i = 0; i < SpawnPointsList.Num(); ++i)
	{
		FVector SpawnLocation = SpawnPointsList[i]->GetActorLocation();
		AIList[i] = Cast<AAICharacter>(GetWorld()->SpawnActor(IAClass, &SpawnLocation, &FRotator::ZeroRotator));
		AIList[i]->SpawnDefaultController();
		AIList[i]->Init(CurrentPlayer, DistanceSafe);
	}
}

void AAIDirector::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	
}
