// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PickUp.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (GetLocalRole() == ROLE_Authority)
	{
		WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolum"));
		RootComponent = WhereToSpawn;
		
		// Some base values
		SpawnDelayRangeLow = 1.0f;
		SpawnDelayRangeHeigh = 4.5f;
	
	}
	


}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	// Set the timer to start spawing pickups
	SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHeigh);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickUp,SpawnDelay, false);

	UE_LOG(LogTemp, Warning, TEXT("Has Authority"));

}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetRandomePointInVolume()
{
	if (WhereToSpawn)
	{
		FVector SpawnOrgin = WhereToSpawn->Bounds.Origin;
		FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;
		return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrgin,SpawnExtent);
	}

	return FVector();
}

void ASpawnVolume::SpawnPickUp()
{
	// If we are the server and we have something to spawn
	if (GetLocalRole() == ROLE_Authority && WhatToSpawn != NULL)
	{
		

		// Check valid world
		if (UWorld* const World = GetWorld())
		{
			// Setup any required params / info
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Where we put the pickup
			FVector SpawnLocation = GetRandomePointInVolume();

			// Set a random rotation for spawn pickup
			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.f;
			SpawnRotation.Pitch = FMath::FRand() * 360.f;
			SpawnRotation.Roll = FMath::FRand() * 360.f;

			// Drop the new pickup to the world
			APickUp* const SpawnedPickup = World->SpawnActor<APickUp>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

			// Delay for a bit before spawning the next pickup
			SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHeigh);
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickUp, SpawnDelay, false);

		}
	}

	
}

