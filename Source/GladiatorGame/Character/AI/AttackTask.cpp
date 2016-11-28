

#include "GladiatorGame.h"
#include "AIController.h"
#include "AICharacter.h"
#include "AttackTask.h"


EBTNodeResult::Type UAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8 * NodeMemory)
{
	AAICharacter* AI = Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	AI->Attack();

	return EBTNodeResult::Succeeded;
}


