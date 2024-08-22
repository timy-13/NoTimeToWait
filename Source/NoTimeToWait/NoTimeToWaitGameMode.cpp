// Copyright Epic Games, Inc. All Rights Reserved.

#include "NoTimeToWaitGameMode.h"
#include "NoTimeToWaitCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANoTimeToWaitGameMode::ANoTimeToWaitGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
