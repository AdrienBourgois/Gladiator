

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "AttackTask.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API UAttackTask : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	
};
