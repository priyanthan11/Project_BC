// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Project_BCCharacter.generated.h"

UCLASS(config=Game)
class AProject_BCCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Collection sphere */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Battery , meta = (AllowPrivateAccess = "true"))
		class USphereComponent* CollectionSphere;
public:
	AProject_BCCharacter();

	// Required Network Setting
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	// Access to starting power
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetInitialPower();
	// Access to Current power
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetCurrentPower();
	/** 
	*This is Update player power level
	@param DeltaPower this is the amount to change power by can be + or -
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Power")
	void UpdatePower(float DeltaPower);

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// Entry called when player prees a key to collect
	UFUNCTION(BlueprintCallable, Category = "pickup")
	void CollectPickups();
	// Called on server to process the collection pick up
	UFUNCTION(Reliable,Server, WithValidation)
	void ServerCollectPickups();
	bool ServerCollectPickups_Validate();
	void ServerCollectPickups_Implementation();
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	// Player starting power level
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected="true"))
	float InitialPower;


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** Returns Collection Sphere subobject **/
	FORCEINLINE class USphereComponent* GetCollectionShpere() const { return CollectionSphere; }

private:

	// Visible radius canbe change in editor
	UPROPERTY(Replicated,VisibleAnywhere, BlueprintReadOnly, Category = "Battery", meta = (AllowPrivateAccess = "true"))
	float CollectionSphereRadius;

	// Character current power level during gameplay
	UPROPERTY(Replicated, VisibleAnywhere, Category = "Power")
	float Currentpower;


};

