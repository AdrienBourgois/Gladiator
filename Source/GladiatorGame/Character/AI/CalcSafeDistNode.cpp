

#include "GladiatorGame.h"
#include "AIController.h"
#include "AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CalcSafeDistNode.h"


EBTNodeResult::Type UCalcSafeDistNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp,	uint8 * NodeMemory)
{
	AAICharacter* AI = Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	AI->CalcVectorSafeDistance();

	return EBTNodeResult::Succeeded;
}

