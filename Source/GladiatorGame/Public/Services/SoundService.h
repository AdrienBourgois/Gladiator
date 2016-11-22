#pragma once

#include "Object.h"
#include "SoundService.generated.h"

UCLASS()
class GLADIATORGAME_API USoundService : public UObject
{
	GENERATED_BODY()
	
public:	

	USoundService();

	enum ESound_Type
	{
		SwordHit,
		DeathCry,
		AttackCry,
	};

	void PlaySound(FVector location, ESound_Type type) const;
	void PlaySound(AActor actor, ESound_Type type) const;

private:

	USoundCue* GetSound(ESound_Type type) const;

	UPROPERTY(EditAnywhere, Category="Sound Class")
	USoundClass* master_mixer = nullptr;
	UPROPERTY(EditAnywhere, Category="Sound Class")
	USoundClass* gameplay_mixer = nullptr;
	UPROPERTY(EditAnywhere, Category="Sound Class")
	USoundClass* mechanics_mixer = nullptr;
	UPROPERTY(EditAnywhere, Category="Sound Class")
	USoundClass* ambiant_mixer = nullptr;
	UPROPERTY(EditAnywhere, Category="Sound Class")
	USoundClass* music_mixer = nullptr;
	UPROPERTY(EditAnywhere, Category="Sound Class")
	USoundClass* ui_mixer = nullptr;

	UPROPERTY(EditAnywhere, Category="Mixer")
	USoundMix* sound_mixer = nullptr;

	UPROPERTY(EditAnywhere, Category="Cues")
	USoundCue* sword_hit_cue = nullptr;
	UPROPERTY(EditAnywhere, Category="Cues")
	USoundCue* death_cry_cue = nullptr;
	UPROPERTY(EditAnywhere, Category="Cues")
	USoundCue* attack_cry_cue = nullptr;

	UAudioComponent* audio_comp = nullptr;

	float time_between_sound = 0.f;
	
	
};
