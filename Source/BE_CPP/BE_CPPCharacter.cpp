// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BE_CPPCharacter.h"
#include "BE_CPPProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);


ABE_CPPCharacter::ABE_CPPCharacter()
{

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);


	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	FPView = CreateDefaultSubobject<UCameraComponent>(TEXT("FPView"));
	FPView->SetupAttachment(GetCapsuleComponent());
	FPView->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); 
	FPView->bUsePawnControlRotation = true;

	CharMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharMesh"));
	CharMesh->SetOnlyOwnerSee(true);
	CharMesh->SetupAttachment(FPView);
	CharMesh->bCastDynamicShadow = false;
	CharMesh->CastShadow = false;
	CharMesh->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	CharMesh->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);


	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetOnlyOwnerSee(true);			
	Weapon->bCastDynamicShadow = false;
	Weapon->CastShadow = false;
	Weapon->SetupAttachment(RootComponent);

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	MuzzleLocation->SetupAttachment(Weapon);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	GunOffset = FVector(100.0f, 0.0f, 10.0f);

}

void ABE_CPPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Weapon->AttachToComponent(CharMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}

void ABE_CPPCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{

	check(PlayerInputComponent);


	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABE_CPPCharacter::CharJump);


	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABE_CPPCharacter::OnFire);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABE_CPPCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABE_CPPCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABE_CPPCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABE_CPPCharacter::LookUpAtRate);
}

void ABE_CPPCharacter::OnFire()
{
	//Bullet Classes aren't in yet, but add logic to spawn different bullet child classes based on AmmoType switch case
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			{
				const FRotator SpawnRotation = GetControlRotation();
				
				const FVector SpawnLocation = ((MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

				
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				
				World->SpawnActor<ABE_CPPProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			}
		}
	}

	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	
	if (FireAnimation != NULL)
	{

		UAnimInstance* AnimInstance = CharMesh->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}



void ABE_CPPCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ABE_CPPCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
	
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ABE_CPPCharacter::TurnAtRate(float Rate)
{

	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABE_CPPCharacter::LookUpAtRate(float Rate)
{
	
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
void ABE_CPPCharacter::CharJump()
{
	if (!isGrounded)
	{
		this->GetCharacterMovement.LaunchCharacter(this, FVector(this->GetVelocity.x, this->GetVelocity.AmmoType, this->GetVelocity.z + JumpHeight), 0, 1);
		isGrounded = true;
	}
	if (!this->GetCharacterMovement.Falling)
	{
		this->GetCharacterMovement.JumpZVelocity = 420;
		this->GetCharacterMovement.GravityScale = 1.6;
		this->Jump();
		isGrounded = false;
	}
}
void ABE_CPPCharacter::Hurt(float Damage)
{
	if (ShieldHealth <= 0.0)
	{
		Health = Health - Damage;
		//UGameplayStatics::PlaySound2D(UObject* WorldContextObject, class USoundBase* Sound, float VolumeMultiplier, float PitchMultiplier, float StartTime)
		//UGameplayStatics::PlayWorldCameraShake();
		if (Health <= 0.0)
		{
			//CHANGE TO RESPAWN FUNCTION WHEN IT EXISTS
			GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
		}
	}
	else
	{
		ShieldHealth = ShieldHealth - Damage;
	}
}
void ABE_CPPCharacter::CountDownCombat()
{
	OOCTimer--;
	if (OOCTimer <= 0.0)
	{
		//this->ResetShield();
		isInCombat = false;
	}
	else
	{
		isInCombat = true;
	}
}
void ABE_CPPCharacter::ResetShield()
{
	//ADD LOGIC ONCE COMBAT IS IN
	//this->initShieldHealth = ShieldHealth;
	
}
void ABE_CPPCharacter::LockOn()
{
	//ADD LOGIC ONCE OTHER LOCKABLE ACTORS ARE IN
	//UKismetSystemLibrary::LineTraceMultiForObjects(GetWorld()->GetFirstLocalPlayerFromController(), 
}