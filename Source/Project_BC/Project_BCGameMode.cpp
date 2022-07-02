// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_BCGameMode.h"
#include "Project_BCCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/HUD.h"

AProject_BCGameMode::AProject_BCGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Set they type of HUD used in the game
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHudClass(TEXT("/Game/Blueprints/BC_HUD_BP"));
	if (PlayerHudClass.Class != NULL)
	{
		HUDClass = PlayerHudClass.Class;
	}

	// Base Decay Rate
	DecayRate = 0.02f;

	//Base Value for how frequantly to drain power
	PowerDrainDelay = 0.25f;
}

void AProject_BCGameMode::BeginPlay()
{
	GetWorldTimerManager().SetTimer(PowerDrainTimer, this, &AProject_BCGameMode::DrainPowerOvertime, PowerDrainDelay, true);

	// Access the world to get to players
	UWorld* World = GetWorld();
	check(World);

	for (FConstControllerIterator It = World->GetControllerIterator(); It; ++It)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(*It))
		{
			if (AProject_BCCharacter* BatteryCharacter = Cast<AProject_BCCharacter>(PlayerController->GetPawn()))
			{
				PowerToWin = BatteryCharacter->GetInitialPower() * 1.25f;
				break;
			}
		}
	}
}

float AProject_BCGameMode::GetDecay()
{
	return DecayRate;
}

float AProject_BCGameMode::GetPowerToWin()
{
	return PowerToWin;
}

void AProject_BCGameMode::DrainPowerOvertime()
{
	// Access the world to get to players
	UWorld* World = GetWorld();
	check(World);

	// Go through all the character in the game
	for (FConstControllerIterator It = World->GetControllerIterator(); It; ++It)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(*It))
		{
			if (AProject_BCCharacter* BatteryCharacter = Cast<AProject_BCCharacter>(PlayerController->GetPawn()))
			{
				if (BatteryCharacter->GetCurrentPower() > 0)
				{
					BatteryCharacter->UpdatePower(-PowerDrainDelay * DecayRate * (BatteryCharacter->GetInitialPower()));
				}
				
			}
		}
	}


}
