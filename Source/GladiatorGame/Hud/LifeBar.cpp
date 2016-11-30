#include "GladiatorGame.h"
#include "LifeBar.h"

float ULifeBar::GetPercent() const
{
	return 1.f / max_life * current_life;
}
