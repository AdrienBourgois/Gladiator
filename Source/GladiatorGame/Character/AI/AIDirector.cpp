// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "AIDirector.h"
#include "AIControl.h"
#include "BehaviorTree/BlackboardComponent.h"

AAIDirector::AAIDirector()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AAIDirector::BeginPlay()
{
	Super::BeginPlay();
	
	if (IAClass == nullptr)
		return;

	AIList.SetNum(SpawnPointsList.Num());
	for (size_t i = 0; i < SpawnPointsList.Num(); ++i)
	{
		FVector SpawnLocation = SpawnPointsList[i]->GetActorLocation();
		AIList[i] = Cast<ACharacter>(GetWorld()->SpawnActor(IAClass, &SpawnLocation, &FRotator::ZeroRotator));
		AIList[i]->SpawnDefaultController();

		AAIControl*	AIController = Cast<AAIControl>(AIList[i]->GetController());
		UBlackboardComponent* BlackBoard = AIController->FindComponentByClass<UBlackboardComponent>();
		BlackBoard->SetValueAsObject("Player", UGameplayStatics::GetPlayerPawn(this, 0));
		BlackBoard->SetValueAsBool("GotoPlayer", true);
	}
}

void AAIDirector::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	
}

void AAIDirector::InitAI()
{

}
