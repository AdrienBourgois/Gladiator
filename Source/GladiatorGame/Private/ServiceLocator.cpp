#include "GladiatorGame.h"
#include "ServiceLocator.h"

UServiceLocator* UServiceLocator::instance;

UServiceLocator* UServiceLocator::GetInstance()
{
    if(instance == nullptr)
    {
        instance = Cast<UServiceLocator>(GEngine->GameSingleton);
        if (!instance) { return nullptr; }
        if (!instance->IsValidLowLevel()) { return nullptr; }
    }
    return instance;
}

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
