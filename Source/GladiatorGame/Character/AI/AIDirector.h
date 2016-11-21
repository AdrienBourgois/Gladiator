// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Character/AI/AICharacter.h"
#include "AIDirector.generated.h"

UCLASS()
class GLADIATORGAME_API AAIDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIDirector();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SpawnAI();

	UPROPERTY(EditAnywhere)
		ACharacter* IACharacter;
	UPROPERTY(EditAnywhere)
		TArray<AActor*>	SpawnPoints;
	UPROPERTY(EditAnywhere)
		int NbEnemy = 5;
private:
	
	TArray<ACharacter*> AIList;

};
