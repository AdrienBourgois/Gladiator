// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "AIDirector.h"


// Sets default values
AAIDirector::AAIDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitAI();

}

// Called when the game starts or when spawned
void AAIDirector::BeginPlay()
{
	Super::BeginPlay();
	
	if (IAClass == nullptr)
		return;

	AIList.SetNum(SpawnPointsList.Num());
	for (size_t i = 0; i < SpawnPointsList.Num(); ++i)
	{

		FVector SpawnLocation = SpawnPointsList[i]->GetActorLocation();
		FActorSpawnParameters Params;
		Params.bNoCollisionFail = true;

		AIList[i] = Cast<ACharacter>(GetWorld()->SpawnActor(IAClass, &SpawnLocation, &FRotator::ZeroRotator, Params));
		AIList[i]->SpawnDefaultController();
	}
}

// Called every frame
void AAIDirector::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	
}

void AAIDirector::InitAI()
{

}
