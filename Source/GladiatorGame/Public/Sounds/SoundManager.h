#pragma once

#include "GameFramework/Actor.h"
#include "SoundManager.generated.h"

UCLASS()
class GLADIATORGAME_API ASoundManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	//virtual void Tick( float DeltaSeconds ) override;

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

	UPROPERTY(EditAnywhere)
	USoundClass* master_mixer = nullptr;
	UPROPERTY(EditAnywhere)
	USoundClass* gameplay_mixer = nullptr;
	UPROPERTY(EditAnywhere)
	USoundClass* mechanics_mixer = nullptr;
	UPROPERTY(EditAnywhere)
	USoundClass* ambiant_mixer = nullptr;
	UPROPERTY(EditAnywhere)
	USoundClass* music_mixer = nullptr;
	UPROPERTY(EditAnywhere)
	USoundClass* ui_mixer = nullptr;

	UPROPERTY(EditAnywhere)
	USoundMix* sound_mixer = nullptr;

	UPROPERTY(EditAnywhere)
	USoundCue* sword_hit_cue = nullptr;
	UPROPERTY(EditAnywhere)
	USoundCue* death_cry_cue = nullptr;
	UPROPERTY(EditAnywhere)
	USoundCue* attack_cry_cue = nullptr;

	UAudioComponent* audio_comp = nullptr;

	float time_between_sound = 0.f;


	
};
