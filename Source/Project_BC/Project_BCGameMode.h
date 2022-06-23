// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Project_BCGameMode.generated.h"

UCLASS(minimalapi)
class AProject_BCGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProject_BCGameMode();

	// Start the powerDrain timer
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Power")
	float GetDecay();

	// How many Times per seconds to update characters power and chech game rules
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power")
	float PowerDrainDelay;

	// Access the timer for recurring power draining
	FTimerHandle PowerDrainTimer;

protected:

	// The rate at which character lose power % per seconds
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintPortected = "true"))
	float DecayRate;

private:

	//Drain power from character and update gameplay
	void DrainPowerOvertime();

};



