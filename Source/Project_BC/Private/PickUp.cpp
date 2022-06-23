// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"
#include "Net/UnrealNetwork.h"

APickUp::APickUp()
{
	// Tells the engine its replicationg
	bReplicates = true;
	// Pickups do not need to tick every seconds
	PrimaryActorTick.bCanEverTick = false;

	if (GetLocalRole() == ROLE_Authority)
	{
		bIsActive = true;

	}


}

void APickUp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APickUp, bIsActive);


}

bool APickUp::IsActive()
{
	return bIsActive;
}

void APickUp::SetActive(bool NewPickUpState)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		bIsActive = NewPickUpState;
	}
}

void APickUp::OnRep_IsActive()
{

}
