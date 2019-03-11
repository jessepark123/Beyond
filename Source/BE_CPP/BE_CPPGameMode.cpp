// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BE_CPPGameMode.h"
#include "BE_CPPHUD.h"
#include "BE_CPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABE_CPPGameMode::ABE_CPPGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/BECharacters/BE_CPP_MainChar"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ABE_CPPHUD::StaticClass();
}
