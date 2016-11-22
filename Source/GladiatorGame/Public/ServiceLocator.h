#pragma once

#include "Object.h"
#include "Services/SoundService.h"
#include "ServiceLocator.generated.h"

UCLASS()
class GLADIATORGAME_API UServiceLocator : public UObject
{
	GENERATED_BODY()

	USoundService* sound;
	static UServiceLocator* instance;

public:
	UServiceLocator();
	~UServiceLocator() = default;

	static UServiceLocator* GetInstance();

	USoundService* GetSoundService() const;
};