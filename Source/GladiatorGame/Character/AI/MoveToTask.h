

#pragma once

#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "MoveToTask.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API UMoveToTask : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector TargetKey;
};
