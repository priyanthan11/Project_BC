// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "PickUp.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_BC_API APickUp : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	// Set Default Value
	APickUp();
	
	//Required network to function
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;

	// Return Wheter or not pick up is active
	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool IsActive();

	// Allow other class to safly Changes pickup Activation state
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetActive(bool NewPickUpState);

protected:

	// True when the pickup is used
	UPROPERTY(ReplicatedUsing = OnRep_IsActive)
	bool bIsActive;

	// THis is called whenerver is active
	UFUNCTION()
	virtual void OnRep_IsActive();

};
