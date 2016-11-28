// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "CharacterPlayer.h"

class AAICharacter : public ACharacter{};

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
	//SetupInputs();
	FindCamera();
	len = FVector::Dist(this->cameraComponent->GetComponentLocation(), this->GetActorLocation());
}

void ACharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->DebugLock(this->lockTarget);
}

bool ACharacterPlayer::AttackEnd()
{
	this->isAttacking = false;
	InputComponent->BindAction("Attack", IE_Pressed, this, &ACharacterPlayer::Attack);
	return true;
}


#pragma endregion

// --- ----- --- //

#pragma region Inputs

void ACharacterPlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	InputComponent->BindAxis("ViewVertical", this, &ACharacterPlayer::VerticalAxis);
	InputComponent->BindAxis("ViewHorizontal", this, &ACharacterPlayer::HorizontalAxis);

	InputComponent->BindAxis("MoveVertical", this, &ACharacterPlayer::VerticalMovement);
	InputComponent->BindAxis("MoveHorizontal", this, &ACharacterPlayer::HorizontalMovement);

	//InputComponent->BindAxis("LockSwitch", this, &ACharacterPlayer::SwitchTarget);

	InputComponent->BindAction("Attack", IE_Pressed, this, &ACharacterPlayer::Attack);
	InputComponent->BindAction("Lock", IE_Pressed, this, &ACharacterPlayer::CallLock);

	InputComponent->BindAction("DebugSwitchLock", IE_Pressed, this, &ACharacterPlayer::SwitchTarget);
}

void ACharacterPlayer::SetupInputs()
{
	InputComponent->BindAxis("ViewVertical", this, &ACharacterPlayer::VerticalAxis);
	InputComponent->BindAxis("ViewHorizontal", this, &ACharacterPlayer::HorizontalAxis);

	InputComponent->BindAxis("MoveVertical", this, &ACharacterPlayer::VerticalMovement);
	InputComponent->BindAxis("MoveHorizontal", this, &ACharacterPlayer::HorizontalMovement);

	//InputComponent->BindAxis("LockSwitch", this, &ACharacterPlayer::SwitchTarget);

	InputComponent->BindAction("Attack", IE_Pressed, this, &ACharacterPlayer::Attack);
	//InputComponent->BindAction("Lock", IE_Pressed, this, &ACharacterPlayer::CallLock);
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
	if (isAttacking)
		return;

	FRotator cur_rotator;
	if (!this->lockTarget)
		cur_rotator = GetControlRotation();
	else
		cur_rotator = this->GetActorRotation();

	cur_rotator.Pitch = 0.0f;
	FVector dir_vector = cur_rotator.Vector();
	AddMovementInput(dir_vector, value * speed * GetWorld()->GetDeltaSeconds());
	this->AdaptView();
}

void ACharacterPlayer::HorizontalMovement(float value)
{
	if (isAttacking)
		return;

	FRotator cur_rotator;
	if (!this->lockTarget)
		cur_rotator = GetControlRotation();
	else
		cur_rotator = this->GetActorRotation(); 
	
	cur_rotator.Pitch = 0.0f;
	FVector dir_vector = cur_rotator.RotateVector(FVector::RightVector.RotateAngleAxis(180.f, FVector::UpVector));
	AddMovementInput(dir_vector, value * speed * GetWorld()->GetDeltaSeconds());
	this->AdaptView();
}


#pragma endregion

// --- ----- --- //

#pragma region Camera Control

bool ACharacterPlayer::IsTargetViewable()
{
	if (!this->HasActiveCameraComponent() || !this->FindCamera())
		return false;

	FVector pos = this->cameraComponent->GetComponentLocation();
	
	TArray<FHitResult> results = TArray<FHitResult>();
	GetWorld()->LineTraceMultiByChannel(results, pos, this->GetActorLocation(), ECollisionChannel::ECC_MAX);
	for (int i =0; i < results.Num(); ++i)
	{
		FHitResult hit = results[i];

		if (hit.Actor->GetClass()->IsChildOf(ABaseCharacter::StaticClass()))
			continue;
		return false;
	}
	return true;
	
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
		CheckDistance(); //Waiting for fix
		return;
	}
	FVector pos = this->cameraComponent->GetComponentLocation();
	FHitResult result = FHitResult();

	GetWorld()->LineTraceSingleByChannel(result, pos, this->GetActorLocation(), ECollisionChannel::ECC_MAX);
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
		
		if (curdist >= minLen)
		{
			float factor = FMath::SmoothStep(0.f, len, curdist);
			this->cameraComponent->SetWorldLocation(this->GetActorLocation() + (dir.GetSafeNormal() * len * factor));
		}
		else
		{
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

#pragma region LockSystem

void ACharacterPlayer::CallLock()
{
	if (this->lockTarget == nullptr)
	{
		this->UpdateEnemyList();
		this->SortEnemyList();
		this->lockTarget = this->FindForwardTarget();
	}
	else
		this->lockTarget = nullptr;

}

void ACharacterPlayer::DebugLock(AActor* target)
{
	FVector pos;
	if (target == nullptr)
		return;
	else
		pos = target->GetActorLocation();

	FVector axis = this->cameraComponent->GetRightVector();
	DrawDebugCircle(GetWorld(), pos, 100.f, 64, FColor::Red, false, -1.f, 0.f, 10.f, axis, this->cameraComponent->GetUpVector(), false);

	FVector2D lookatdir = FVector2D(pos) - FVector2D(this->GetActorLocation());
	this->SetActorRotation(FRotationMatrix::MakeFromX(FVector(lookatdir, 0.f)).Rotator());

}

TArray<AActor*> ACharacterPlayer::UpdateEnemyList()
{
	this->enemy_array.Empty();
	this->enemy_map.Empty();

	for (TActorIterator<AAICharacter> enemy(GetWorld()); enemy; ++enemy)
	{
		AAICharacter* current = *enemy;
		if (current->GetClass() != this->GetClass())
		{
			AActor* cur_actor = Cast<AActor>(current);
			this->enemy_array.Add(cur_actor);
			this->enemy_map.Add(this->GetActorPositionFactor(cur_actor), cur_actor);
		}
	}

	return this->enemy_array;
}

void ACharacterPlayer::SortEnemyList()
{
	TMap< float, AActor*> raw = TMap< float, AActor*>();
	TArray<float> factors = TArray<float>();

	for (int i = 0; i < this->enemy_array.Num(); ++i)
	{
		float curfactor = this->GetActorPositionFactor(this->enemy_array[i]);
		raw.Add(curfactor,this->enemy_array[i]);
		factors.Add(curfactor);
	}

	factors.Sort();
	this->enemy_map.Empty();

	for (int i = 0; i < factors.Num(); ++i)
	{
		this->enemy_map.Add(factors[i], raw[factors[i]]);
		this->enemy_array[factors.IndexOfByKey(factors[i])] = raw[factors[i]];
	}

	
}

float ACharacterPlayer::GetActorPositionFactor(AActor* factorized)
{
	FVector pos = factorized->GetActorLocation();
	float raw = ACharacterPlayer::GetAngleBetween(factorized->GetActorLocation() - this->GetActorLocation(), this->GetActorForwardVector());
	float ref = raw * this->GetLRFactor(this, factorized);
	return ref;
}

AActor* ACharacterPlayer::FindForwardTarget()
{
	TArray<float> keys = TArray<float>();
	this->enemy_map.GetKeys(keys);

	for (int i = 0; i < keys.Num(); ++i)
	{
		bool isMin = true;
		for (int j = 0; j < keys.Num(); ++j)
		{
			if (i == j)
				continue;
			
			if (FMath::Abs(keys[i]) > FMath::Abs(keys[j]))
			{
				isMin = false;
				break;
			}
		}
		if (!isMin)
			continue;

		return this->enemy_map[keys[i]];
	}
	return nullptr;
}

AActor* ACharacterPlayer::FindNearestEnemyFrom(FVector pos)
{
	float minlen = FMath::Pow(ONE_METER, ONE_METER);

	for (int i = 0; i < this->enemy_array.Num(); ++i)
	{
		AActor* actorI = this->enemy_array[i];
		for (int j = 0; i < this->enemy_array.Num(); ++i)
		{
			AActor* actorJ = this->enemy_array[j];
			if (actorI == actorJ)
				continue;

			minlen = FMath::Min(FVector::Dist(pos , actorI->GetActorLocation()), FVector::Dist(pos, actorJ->GetActorLocation()));
		}
	}

	AActor* result = nullptr;

	for (int i = 0; i < this->enemy_array.Num(); ++i)
	{
		AActor* actorI = this->enemy_array[i];
		if (FVector::Dist(pos, actorI->GetActorLocation()))
		{
			result = actorI;
			return result;
		}
	}

	return result;
}

void ACharacterPlayer::SwitchTarget(/*float value*/)
{
	int value = 1;	//Waiting for fix on mouse wheel axis binding

	if (!this->lockTarget)
		return;

	TArray<float> keys = TArray<float>();
	enemy_map.GetKeys(keys);
	float curkey = *enemy_map.FindKey(this->lockTarget);

	int idx = keys.IndexOfByKey(curkey) + value ;
	if (idx >= keys.Num())
		idx = 0;
	else if (idx < 0)
		idx = keys.Num() - 1;

	this->lockTarget = enemy_map[keys[idx]];
}

#pragma endregion

// --- ----- --- //

#pragma region Utilities

float ACharacterPlayer::GetAngleBetween(FVector V1, FVector V2)
{
	return FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(V1.GetSafeNormal(), V2.GetSafeNormal())));
}

int ACharacterPlayer::GetLRFactor(AActor* ref_actor, AActor* tested_actor)
{
	FVector refpos = ref_actor->GetActorLocation();
	FVector testpos = tested_actor->GetActorLocation();

	float LDist = FVector::Dist(refpos - ref_actor->GetActorRightVector(), testpos);
	float RDist = FVector::Dist(refpos + ref_actor->GetActorRightVector(), testpos);

	if (LDist < RDist)
		return LFACTOR;
	else if (RDist < LDist)
		return RFACTOR;

	return 0;
}

#pragma endregion 

// --- ----- --- //