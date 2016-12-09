

#include "GladiatorGame.h"
#include "GladiatorGameState.h"
#include "GladiatorGameController.h"
#include "ServiceLocator.h"


void AGladiatorGameState::PlayerWin()
{
	Cast<AGladiatorGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->DisplayEndGameMenu("Player Win");
	UServiceLocator::GetInstance()->GetSoundService();
}

void AGladiatorGameState::AIWin()
{
	Cast<AGladiatorGameController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->DisplayEndGameMenu("Enemy Win");
}
