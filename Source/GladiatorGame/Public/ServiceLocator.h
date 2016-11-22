#pragma once

#include "Object.h"
#include "Services/SoundService.h"
#include "ServiceLocator.generated.h"

UCLASS()
class GLADIATORGAME_API UServiceLocator : public UObject
{
	GENERATED_BODY()

	USoundService* sound;

public:
	UServiceLocator();
	~UServiceLocator();

	USoundService* GetSoundService() const;
};
