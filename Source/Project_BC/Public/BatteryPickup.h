// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUp.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_BC_API ABatteryPickup : public APickUp
{
	GENERATED_BODY()
	
public:
	// Set default values for instances of class
	ABatteryPickup();

	// Required Network Setting
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	//Server side handling being picked up by the child class
	//UFUNCTION(BlueprintAuthorityOnly, Category = "PickUp")
	void PickedUpBY(APawn* Pawn) override;

	// Public metheod to access the battery power leven
	float GetPower();


protected:

	// Set Amount of power the battery holds
	UPROPERTY(Replicated,EditAnywhere,BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	float BatteryPower;

};
