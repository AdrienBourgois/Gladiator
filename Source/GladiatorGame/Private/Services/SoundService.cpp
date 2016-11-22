#include "GladiatorGame.h"
#include "Services/SoundService.h"
#include "ServiceLocator.h"

USoundService::USoundService()
{
    audio_comp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
}

USoundCue* USoundService::GetSound(ESound_Type type) const
{
    switch (type)
    {
        case SwordHit: return sword_hit_cue;
        case DeathCry: return death_cry_cue;
        case AttackCry: return attack_cry_cue;
        default: break;
    }
    return nullptr;
}

void USoundService::PlaySound(FVector location, ESound_Type type) const
{
    audio_comp->SetSound(GetSound(type));
    audio_comp->Play();
    audio_comp->RelativeLocation = location;
}

void USoundService::PlaySound(AActor actor, ESound_Type type) const
{
    audio_comp->SetSound(GetSound(type));
    audio_comp->Play();
    audio_comp->RelativeLocation = actor.GetActorLocation();
}


