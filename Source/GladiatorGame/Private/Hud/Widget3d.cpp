#include "GladiatorGame.h"
#include "Widget3d.h"

// Sets default values for this component's properties
UWidget3d::UWidget3d()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

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

    if (widget_component)
    {
        if (actor_to_follow)
        {
            FVector compute_location = actor_to_follow->GetActorLocation() + relative_location_from_actor;
            if(fly_animation)
            {
                current_fly_location += FVector(0.f, 0.f, 25.f * DeltaTime);
                if (current_fly_location.Z > max_z_fly)
                {
                    fly_animation = false;
                    Destruct();
                    return;
                }
                compute_location += current_fly_location;
            }
            widget_component->SetWorldLocation(compute_location);
        }

        if (camera_manager)
        {
            FVector delta_position = camera_manager->GetCameraLocation() - widget_component->GetComponentLocation();
            delta_position.Normalize();
            FRotator rotation = delta_position.Rotation();
            widget_component->SetWorldRotation(rotation);
        }
    }
}

void UWidget3d::Follow(TSubclassOf<UUserWidget> _type, int init_value, FVector _relative_location, bool _fly_animation)
{
    PrimaryComponentTick.bCanEverTick = true;

    fly_animation = _fly_animation;

    //Temporary fix
    /*if (init_value <= 0)
    {
        widget_component->DestroyComponent();
        DestroyComponent();
        return;
    }*/

    actor_to_follow = GetOwner();
    relative_location_from_actor = _relative_location;

    widget_component = NewObject<UWidgetComponent>(this, TEXT("WidgetComponentInstance"));
    widget_component->SetWidgetClass(_type);
    widget_component->SetWorldLocation(actor_to_follow->GetActorLocation() + relative_location_from_actor);
    widget_component->SetDrawSize(FVector2D(200, 50));
    widget_component->SetVisibility(true);
    widget_component->RegisterComponent();
    widget_instance = widget_component->GetUserWidgetObject();

    IWidgetInterface::Execute_InitWidget(widget_component->GetUserWidgetObject(), init_value);

    camera_manager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
}

void UWidget3d::Action(int value) const
{
       IWidgetInterface::Execute_ActionWidget(widget_component->GetUserWidgetObject(), value);
}

void UWidget3d::Destruct()
{
    PrimaryComponentTick.bCanEverTick = false;
    widget_component->DestroyComponent();
    widget_component = nullptr;
    widget_instance->Destruct();
    widget_instance = nullptr;
    DestroyComponent();
}
