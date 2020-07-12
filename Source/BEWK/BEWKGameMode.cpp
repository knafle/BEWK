// Copyright Epic Games, Inc. All Rights Reserved.

#include "BEWKGameMode.h"
#include "BEWKPlayerController.h"
#include "BEWKCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABEWKGameMode::ABEWKGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ABEWKPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}