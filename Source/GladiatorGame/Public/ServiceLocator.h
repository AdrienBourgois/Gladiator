#pragma once

#include "Object.h"
#include "Services/SoundService.h"
#include "ServiceLocator.generated.h"

UCLASS(Blueprintable)
class GLADIATORGAME_API UServiceLocator : public UObject
{
	GENERATED_BODY()

	USoundService* sound;
	static UServiceLocator* instance;

public:
	UServiceLocator();

	static UServiceLocator* GetInstance();

	USoundService* GetSoundService() const;
};