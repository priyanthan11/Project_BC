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

	// Function to call when the pickup is collected
	UFUNCTION(BlueprintNativeEvent, Category = "PickUp")
	void WasCollected();
	virtual void WasCollected_Implementation();

	//Server side handling being picked up
	UFUNCTION(BlueprintAuthorityOnly, Category ="PickUp")
	virtual void PickedUpBY(APawn* Pawn);

protected:

	// True when the pickup is used
	UPROPERTY(ReplicatedUsing = OnRep_IsActive)
	bool bIsActive;

	// THis is called whenerver is active
	UFUNCTION()
	virtual void OnRep_IsActive();
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category ="PickUp")
	APawn* PickUpInstigator;
	
private:
	// Client side handing of being picked up
	UFUNCTION(NetMulticast,Unreliable)
	void ClientOnPickedUpBy(APawn* Pawn);
	void ClientOnPickedUpBy_Implementation(APawn* Pawn);

};
