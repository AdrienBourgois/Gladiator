// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "AIDirector.h"
#include "GladiatorGameState.h"

AAIDirector* AAIDirector::instance;

AAIDirector::AAIDirector()
{
	PrimaryActorTick.bCanEverTick = true;
	IAClass = nullptr;
	CurrentPlayer = nullptr;
	instance = this;
}

void AAIDirector::BeginPlay()
{
	Super::BeginPlay();
	
	if (IAClass == nullptr)
		return;
	CurrentPlayer = Cast<AActor>(UGameplayStatics::GetPlayerPawn(this, 0));

	AIList.SetNum(SpawnPointsList.Num());
	for (size_t i = 0; i < AIList.Num(); ++i)
	{
		FVector SpawnLocation = SpawnPointsList[i]->GetActorLocation();
		AIList[i] = Cast<AAICharacter>(GetWorld()->SpawnActor(IAClass, &SpawnLocation, &FRotator::ZeroRotator));
		AIList[i]->SpawnDefaultController();
		AIList[i]->Init(this, CurrentPlayer, DistanceSafe, DistanceToOtherAI);
	}
	ChoiceGoToPlayer();
}

AAIDirector* AAIDirector::GetAIDirector()
{
	if(!instance)
	{
		return nullptr;
	}
	return instance;
}

void AAIDirector::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AAIDirector::ChoiceGoToPlayer()
{
	if (AIList.Num() <= 0)
		return;

	int idx = FMath::RandRange(0, AIList.Num()-1);
	if (AIList[idx]->GetState() == StateAI::GoSafe)
	{
		AIList[idx]->SetState(StateAI::GoToPlayer);
	}
	GetWorld()->GetTimerManager().SetTimer(GotoPlayerTimerHandle, this, &AAIDirector::ChoiceGoToPlayer, 1.0f, false, TimeGoToPlayer);
}

ADroppable* AAIDirector::GoToWeapon(USceneComponent* ref)
{
	for (int i =0; i < EquipmentList.Num(); i++)
	{
		if (EquipmentList[i]->IsSameAs(Cast<USkeletalMeshComponent>(ref)))
			return EquipmentList[i];
	}
	return nullptr;
}

void AAIDirector::DeathAI(AAICharacter* Target)
{
	AIList.Remove(Target);
	if (AIList.Num() <= 0)
	{
		Cast<AGladiatorGameState>(GetWorld()->GetGameState())->PlayerWin();
	}
}