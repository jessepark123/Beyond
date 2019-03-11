// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "BE_CPPProjectile.generated.h"


UCLASS(config=Game)
class ABE_CPPProjectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	class USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	

public:
	ABE_CPPProjectile();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UParticleSystem*  BulletParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Audio)
		USoundCue* A_Explosion;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AActor* Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

