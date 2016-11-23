// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DistanceDecorator.h"


bool UDistanceDecorator::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	AActor* AI =  OwnerComp.GetAIOwner()->GetPawn();
	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey.SelectedKeyName));

	if (AI->GetDistanceTo(TargetActor) < (Distance - RangeDistance) && AI->GetDistanceTo(TargetActor) > (Distance + RangeDistance))
		return true;
	else
		return false;
}

