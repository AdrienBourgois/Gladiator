

#include "GladiatorGame.h"
#include "GladiatorGameState.h"


void AGladiatorGameState::PlayerWin()
{
	UE_LOG(LogTemp, Warning, TEXT("PLAYER WIN!!!!!!"));
	UGameplayStatics::OpenLevel(GetWorld(), "AI_test");
}

void AGladiatorGameState::AIWin()
{
	UE_LOG(LogTemp, Warning, TEXT("AI WIN!!!!!!"));
	UGameplayStatics::OpenLevel(GetWorld(), "AI_test");
}
