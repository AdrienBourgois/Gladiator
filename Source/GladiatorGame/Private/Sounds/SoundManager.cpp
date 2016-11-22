#include "GladiatorGame.h"
#include "Public/Sounds/SoundManager.h"

// Sets default values
ASoundManager::ASoundManager()
{
    check(!(master_mixer && gameplay_mixer && mechanics_mixer && ambiant_mixer && music_mixer && ui_mixer && sound_mixer && sword_hit_cue && death_cry_cue && attack_cry_cue) && "SoundManager : Forget to assigned an element !");
    
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    
    audio_comp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
}

// Called when the game starts or when spawned
void ASoundManager::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
//void ASoundManager::Tick( float DeltaTime )
//{
//    Super::Tick( DeltaTime );
//}

USoundCue* ASoundManager::GetSound(ESound_Type type) const
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

void ASoundManager::PlaySound(FVector location, ESound_Type type) const
{
    audio_comp->SetSound(GetSound(type));
    audio_comp->Play();
    audio_comp->RelativeLocation = location;
}

void ASoundManager::PlaySound(AActor actor, ESound_Type type) const
{
    audio_comp->SetSound(GetSound(type));
    audio_comp->Play();
    audio_comp->RelativeLocation = actor.GetActorLocation();
}
