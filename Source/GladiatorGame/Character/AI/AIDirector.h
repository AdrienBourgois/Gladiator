// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AICharacter.h"
#include "AIDirector.generated.h"

UCLASS()
class GLADIATORGAME_API AAIDirector : public AActor
{
	GENERATED_BODY()
	
public:	

	AAIDirector();
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		UClass* IAClass;
	UPROPERTY(EditAnywhere)
		TArray<AActor*>	SpawnPointsList;
	UPROPERTY(EditAnywhere)
		int NbEnemy = 5;
	UPROPERTY(EditAnywhere)
		float DistanceSafe = 500.f;

private:
	AActor* CurrentPlayer;
	TArray<AAICharacter*> AIList;

};
