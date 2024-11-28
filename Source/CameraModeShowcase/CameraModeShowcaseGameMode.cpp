// Copyright Epic Games, Inc. All Rights Reserved.

#include "CameraModeShowcaseGameMode.h"
#include "CameraModeShowcaseCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACameraModeShowcaseGameMode::ACameraModeShowcaseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
