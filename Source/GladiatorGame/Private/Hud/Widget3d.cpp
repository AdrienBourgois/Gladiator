#include "GladiatorGame.h"
#include "Widget3d.h"

// Sets default values for this component's properties
UWidget3d::UWidget3d()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}

// Called when the game starts
void UWidget3d::BeginPlay()
{
    Super::BeginPlay();
    
    // ...
}

// Called every frame
void UWidget3d::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
    Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    // ...

    if(widget_component && actor_to_follow)
        widget_component->SetWorldLocation(actor_to_follow->GetActorLocation() + relative_location_from_actor);
}

void UWidget3d::Follow(TSubclassOf<UUserWidget> _type, FVector _relative_location)
{
    PrimaryComponentTick.bCanEverTick = true;

    actor_to_follow = GetOwner();
    relative_location_from_actor = _relative_location;

    widget_component = NewObject<UWidgetComponent>(this, TEXT("WidgetComponentInstance"));
    widget_component->SetWidgetClass(_type);
    widget_component->SetWorldLocation(actor_to_follow->GetActorLocation() + relative_location_from_actor);
    widget_component->SetDrawSize(FVector2D(200, 50));
    widget_component->RegisterComponent();
    widget_instance = widget_component->GetUserWidgetObject();

    //UE_LOG(LogTemp, Warning, TEXT("Owner : %s"), *widget_component->GetOwner()->GetName());

    PrimaryComponentTick.bCanEverTick = true;
}