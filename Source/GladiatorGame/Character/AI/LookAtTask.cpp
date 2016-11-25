

#include "GladiatorGame.h"
#include "AIController.h"
#include "AICharacter.h"
#include "LookAtTask.h"

EBTNodeResult::Type ULookAtTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8 * NodeMemory)
{
	AAICharacter* AI = Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	AI->LookAt();

	return EBTNodeResult::Succeeded;
}


