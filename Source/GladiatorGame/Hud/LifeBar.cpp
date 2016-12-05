#include "GladiatorGame.h"
#include "LifeBar.h"

float ULifeBar::GetPercent() const
{
	return 1.f / max_life * current_life;
}

FString ULifeBar::GetCurrentLifeAsText() const
{
	return FString::SanitizeFloat(current_life);
}

void ULifeBar::InitWidget_Implementation(int value)
{
	max_life = value;
	current_life = value;
}

void ULifeBar::ActionWidget_Implementation(int value)
{
	current_life -= value;
}
