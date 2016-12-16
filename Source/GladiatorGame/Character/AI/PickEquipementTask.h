

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "PickEquipementTask.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API UPickEquipementTask : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	
};
