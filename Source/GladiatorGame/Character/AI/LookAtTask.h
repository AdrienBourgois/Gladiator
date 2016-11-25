

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "LookAtTask.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API ULookAtTask : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	
};
