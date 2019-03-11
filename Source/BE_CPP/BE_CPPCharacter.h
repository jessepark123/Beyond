// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BE_CPPCharacter.generated.h"
#include <iostream>
#include <string>


class UInputComponent;

UCLASS(config=Game)
class ABE_CPPCharacter : public ACharacter
{
	GENERATED_BODY()

	//Initializing Character Class Properties

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
		class USkeletalMeshComponent* CharMesh;


	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* Weapon;


	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* MuzzleLocation;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FPView;


public:
	ABE_CPPCharacter();

protected:
	virtual void BeginPlay();

public:

	//Variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BulletSpeed = 4500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isMapExpanded = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AmmoType = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isHoldingTrigger = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AmmoType_Temp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor LockableActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool RightBumperPressed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor EmptyActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LockOnText = "LB";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool pressedLeftShoulder = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Health = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int NumJumps = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isSpacePressed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isGrounded = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float JumpHeight = 800;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float initHealth = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor GunEmissive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ShieldHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float OOCTimer = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float initShieldHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isInCombat = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isShieldRecharging = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
		float BaseTurnRate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
		float BaseLookUpRate;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
		FVector GunOffset;


	UPROPERTY(EditDefaultsOnly, Category=Projectile)
		TSubclassOf<class ABE_CPPProjectile> ProjectileClass;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
		class USoundBase* FireSound;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;


protected:
	
	//Functions

	void OnFire();
	
	void MoveForward(float Val);

	
	void MoveRight(float Val);


	void TurnAtRate(float Rate);


	void LookUpAtRate(float Rate);

	UFUNCTION(BlueprintCallable)
	void CharJump();

	UFUNCTION(BlueprintCallable)
	void Hurt(float Damage);

	UFUNCTION(BlueprintCallable)
	void CountDownCombat();

	UFUNCTION(BlueprintCallable)
	void ResetShield();

	UFUNCTION(BlueprintCallable)
	void LockOn();
	
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:

	FORCEINLINE class USkeletalMeshComponent* GetCharMesh() const { return CharMesh; }

	FORCEINLINE class UCameraComponent* GetFPView() const { return FPView; }

};

