// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BE_CPPProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Engine.h"
#include "BE_CPPCharacter.h"
#include <iostream>

ABE_CPPProjectile::ABE_CPPProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ABE_CPPProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ABE_CPPProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FName SocketName = "";

	if (OtherActor != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hit"));
	}
	UGameplayStatics::SpawnEmitterAttached(BulletParticle, HitComp, SocketName, FVector(0, 0, 0), FRotator(0, 0, 0), FVector(0, 0, 0), EAttachLocation::KeepRelativeOffset, true, EPSCPoolMethod::None);
	
	UGameplayStatics::PlaySoundAtLocation(Player, A_Explosion, FVector(this->GetActorLocation()), 1.0F, 1.0F, 0.0F);
	
	Destroy();
}