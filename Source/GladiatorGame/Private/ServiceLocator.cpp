#include "GladiatorGame.h"
#include "ServiceLocator.h"


UServiceLocator::UServiceLocator()
{
	sound = NewObject<USoundService>(this, TEXT("SoundManager"));
}

UServiceLocator::~UServiceLocator()
{}

USoundService* UServiceLocator::GetSoundService() const
{
	return sound;
}
