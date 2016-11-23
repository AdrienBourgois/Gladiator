

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CalcSafeDistNode.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API UCalcSafeDistNode : public UBTTaskNode
{
	GENERATED_BODY()
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector TargetKey;
	
};
