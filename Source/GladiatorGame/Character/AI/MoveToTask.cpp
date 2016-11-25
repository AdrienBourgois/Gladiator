

#include "GladiatorGame.h"
#include "AIController.h"
#include "AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MoveToTask.h"


EBTNodeResult::Type UMoveToTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8 * NodeMemory)
{
	AAICharacter* AI = Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	FVector Target = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TargetKey.SelectedKeyName);
	AI->MoveTo(Target);

	return EBTNodeResult::Succeeded;
}


