// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "CharacterPlayer.h"

// --- ----- --- //

#pragma region Default Functions

// Sets default values
ACharacterPlayer::ACharacterPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	SetupInputs();
	FindCamera();
	len = FVector::Dist(this->cameraComponent->GetComponentLocation(), this->GetActorLocation());
}

void ACharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#pragma endregion

// --- ----- --- //

#pragma region Inputs

void ACharacterPlayer::SetupInputs()
{
	InputComponent->BindAxis("ViewVertical", this, &ACharacterPlayer::VerticalAxis);
	InputComponent->BindAxis("ViewHorizontal", this, &ACharacterPlayer::HorizontalAxis);

	InputComponent->BindAxis("MoveVertical", this, &ACharacterPlayer::VerticalMovement);
	InputComponent->BindAxis("MoveHorizontal", this, &ACharacterPlayer::HorizontalMovement);

	InputComponent->BindAction("Attack", IE_Pressed, this, &ACharacterPlayer::Attack);
}

void ACharacterPlayer::VerticalAxis(float value)
{
	float rotation = value * sensitivity * GetWorld()->GetDeltaSeconds();
	AddControllerPitchInput(rotation);
	this->AdaptView();
}

void ACharacterPlayer::HorizontalAxis(float value)
{
	float rotation = value * sensitivity * GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(rotation);
	this->AdaptView();
}

void ACharacterPlayer::VerticalMovement(float value)
{
	FRotator cur_rotator = GetControlRotation();
	cur_rotator.Pitch = 0.0f;
	FVector dir_vector = cur_rotator.Vector();
	AddMovementInput(dir_vector, value * speed * GetWorld()->GetDeltaSeconds());
	this->AdaptView();
}

void ACharacterPlayer::HorizontalMovement(float value)
{
	FRotator cur_rotator = GetControlRotation();
	cur_rotator.Pitch = 0.0f;
	FVector dir_vector = cur_rotator.RotateVector(FVector::RightVector.RotateAngleAxis(180.f, FVector::UpVector));
	AddMovementInput(dir_vector, value * speed * GetWorld()->GetDeltaSeconds());
	this->AdaptView();
}

void ACharacterPlayer::Attack()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, "Attack Not Implemented Yet");

}

#pragma endregion

// --- ----- --- //

#pragma region Camera Control

bool ACharacterPlayer::IsTargetViewable()
{
	if (!this->HasActiveCameraComponent() || !this->FindCamera())
		return false;

	FVector pos = this->cameraComponent->GetComponentLocation();

	FHitResult result = FHitResult();

	GetWorld()->LineTraceSingleByChannel(result, pos, this->GetActorLocation(), ECollisionChannel::ECC_WorldStatic);

	return (result.Actor == this);
}

bool ACharacterPlayer::IsTargetInRange()
{
	FVector pos = this->cameraComponent->GetComponentLocation();
	FHitResult result = FHitResult();

	GetWorld()->LineTraceSingleByChannel(result, pos, this->GetActorLocation(), ECollisionChannel::ECC_WorldStatic);

	return (result.Distance >= minLen);
}

void ACharacterPlayer::AdaptView()
{
	if (IsTargetViewable())
	{
		if (IsTargetInRange())
			CheckDistance();
		else
			CheckDistance(); //Waiting for fix
		return;
	}
	FVector pos = this->cameraComponent->GetComponentLocation();
	FHitResult result = FHitResult();

	GetWorld()->LineTraceSingleByChannel(result, pos, this->GetActorLocation(), ECollisionChannel::ECC_WorldStatic);
	AdaptFromCollision(result.ImpactPoint);
}

void ACharacterPlayer::AdaptFromCollision(FVector collider)
{
	if (this->cameraComponent && FVector::Dist(collider, this->GetActorLocation()) >= minLen)
		this->cameraComponent->SetWorldLocation(collider);
}

void ACharacterPlayer::CheckDistance()
{
	float curdist = FVector::Dist(this->cameraComponent->GetComponentLocation(), this->GetActorLocation());
	if (curdist < len)
	{
		FVector dir = this->cameraComponent->GetComponentLocation() - this->GetActorLocation();
		float factor = FMath::SmoothStep(0.f, len, curdist);
		this->cameraComponent->SetWorldLocation(this->GetActorLocation() + (dir.GetSafeNormal() * len * factor));

		if (curdist < minLen)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::SanitizeFloat(curdist));
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, dir.GetSafeNormal().ToString());
			dir = -this->Controller->GetControlRotation().Vector();
			this->cameraComponent->SetWorldLocation(this->GetActorLocation() + (dir.GetSafeNormal() * minLen * 2));
		}
	}

}

UCameraComponent* ACharacterPlayer::FindCamera()
{
	TInlineComponentArray<UCameraComponent*> Cameras;
	GetComponents<UCameraComponent>(Cameras);

	for (UCameraComponent* CameraComponent : Cameras)
		if (CameraComponent->bIsActive)
			this->cameraComponent = CameraComponent;

	return this->cameraComponent;
}

#pragma endregion

// --- ----- --- //
