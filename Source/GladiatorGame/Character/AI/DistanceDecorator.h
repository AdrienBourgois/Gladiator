// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "DistanceDecorator.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API UDistanceDecorator : public UBTDecorator
{
	GENERATED_BODY()

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)const override;

public:
	UPROPERTY(EditAnywhere)
		float Distance = 100.f;
	UPROPERTY(EditAnywhere)
		float RangeDistance = 100.f;
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector TargetKey;

};
