// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class PROJECT_BC_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ReturnSpawnVolumes Box Component
	FORCEINLINE class UBoxComponent* GetWheretoSpawn() const { return WhereToSpawn; }

	// Find Randome Point within box/Map
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomePointInVolume();

protected:

	//This is pickup to spawn
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf <class APickUp> WhatToSpawn;

	// Access to the timer for spawn
	FTimerHandle SpawnTimer;

	// Minum Spawn Delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeLow;

	// Heigh Spawn Delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeHeigh;


private:

	//This is spawn area where pickup were created
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WhereToSpawn;

	//Handle spawn pickup
	void SpawnPickUp();
	// Actual Time in seconds befor spawning next pickup
	float SpawnDelay;


};
