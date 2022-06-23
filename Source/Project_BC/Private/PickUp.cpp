// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"
#include "Net/UnrealNetwork.h"

APickUp::APickUp()
{
	// Tells the engine its replicationg
	bReplicates = true;
	// Pickups do not need to tick every seconds
	PrimaryActorTick.bCanEverTick = false;

	GetStaticMeshComponent()->SetGenerateOverlapEvents(true);

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


void APickUp::WasCollected_Implementation()
{

	// Log a debug message

	UE_LOG(LogClass, Log, TEXT("APickUp::WasCollected_Implementation() %S"), *GetName());

}

void APickUp::PickedUpBY(APawn* Pawn)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		PickUpInstigator = Pawn;
		// Notify client of the picked up Action
		ClientOnPickedUpBy(Pawn);
	}

}

void APickUp::ClientOnPickedUpBy_Implementation(APawn* Pawn)
{
	//Store the pawn who picked up(Client)
	PickUpInstigator = Pawn;
	//Fire Blueprint Native Event, Which it self cannot be replicated
	WasCollected();
}