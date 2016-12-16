

#include "GladiatorGame.h"
#include "AIController.h"
#include "AICharacter.h"
#include "PickEquipementTask.h"


EBTNodeResult::Type UPickEquipementTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8 * NodeMemory)
{
	AAICharacter* AI = Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	AI->TryPickEquipment();

	return EBTNodeResult::Succeeded;
}

