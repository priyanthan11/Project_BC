// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_BCGameMode.h"
#include "Project_BCCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProject_BCGameMode::AProject_BCGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
