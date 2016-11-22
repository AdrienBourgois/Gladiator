// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "Camera.h"


// Sets default values
ACamera::ACamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACamera::BeginPlay()
{
	Super::BeginPlay();
	SetupInputs();
	FindCamera();
	len = FVector::Dist(this->camera->GetComponentLocation(), this->GetActorLocation());
}

// Called every frame
void ACamera::Tick( float DeltaTime )
{
	this->AdaptView();
	Super::Tick( DeltaTime );

}

void ACamera::SetupInputs()
{
	InputComponent->BindAxis("ViewVertical", this, &ACamera::VerticalAxis);
	InputComponent->BindAxis("ViewHorizontal", this, &ACamera::HorizontalAxis);
}

void ACamera::VerticalAxis(float value)
{
	float rotation = value * sensitivity * GetWorld()->GetDeltaSeconds();
	AddControllerPitchInput(rotation);
}

void ACamera::HorizontalAxis(float value)
{
	float rotation = value * sensitivity * GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(rotation);
}

bool ACamera::IsTargetViewable()
{
	if (!this->HasActiveCameraComponent() || !this->FindCamera())
		return false;

	FVector pos = FVector();
	FHitResult result = FHitResult();
	
	pos = this->camera->GetComponentLocation();
	
	bool raw = GetWorld()->LineTraceSingleByChannel(result, pos, this->GetActorLocation(), ECollisionChannel::ECC_WorldStatic);

	if (result.Distance < minLen)
		return false;

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "inception lock");


	return (result.Actor == this);
}

void ACamera::AdaptView()
{
	if (IsTargetViewable())
	{
		CheckDistance();
		return;
	}
	FVector pos = this->camera->GetComponentLocation();
	FHitResult result = FHitResult();

	GetWorld()->LineTraceSingleByChannel(result, pos, this->GetActorLocation(), ECollisionChannel::ECC_WorldStatic);
	AdaptFromCollision(result.ImpactPoint);
}

void ACamera::AdaptFromCollision(FVector collider)
{
	if (this->camera && FVector::Dist(collider, this->GetActorLocation()) >= minLen)
		this->camera->SetWorldLocation(collider);
}

void ACamera::CheckDistance()
{
	float curdist = FVector::Dist(this->camera->GetComponentLocation(), this->GetActorLocation());
	if (curdist < len)
	{
		FVector dir = this->camera->GetComponentLocation() - this->GetActorLocation();
		float factor = FMath::SmoothStep(0.f, len, curdist);
		this->camera->SetWorldLocation(this->GetActorLocation() + (dir.GetSafeNormal() * len * factor));

		if (curdist < minLen)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::SanitizeFloat(curdist));
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, dir.GetSafeNormal().ToString());
			dir = -this->Controller->GetControlRotation().Vector();
			this->camera->SetWorldLocation(this->GetActorLocation() + (dir.GetSafeNormal() * minLen * 2));
		}
	}
	
}

UCameraComponent* ACamera::FindCamera()
{
	TInlineComponentArray<UCameraComponent*> Cameras;
	GetComponents<UCameraComponent>(/*out*/ Cameras);

	for (UCameraComponent* CameraComponent : Cameras)
		if (CameraComponent->bIsActive)
			this->camera = CameraComponent;
	
	return this->camera;
}
