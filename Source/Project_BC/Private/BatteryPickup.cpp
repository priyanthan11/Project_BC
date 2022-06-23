// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryPickup.h"
#include <Runtime/Engine/Public/Net/UnrealNetwork.h>

ABatteryPickup::ABatteryPickup()
{
	// Keep Movement sync from server to client
	SetReplicateMovement(true);

	// Physics Enabled and moveable
	GetStaticMeshComponent()->SetSimulatePhysics(true);
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);

	// Settup Base Value for power
	BatteryPower = 200.f;

}

void ABatteryPickup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABatteryPickup, BatteryPower);

}

void ABatteryPickup::PickedUpBY(APawn* Pawn)
{
	Super::PickedUpBY(Pawn);

	if (GetLocalRole() == ROLE_Authority)
	{
		//given clients time to play vfx, etc.. before battery destroy
		SetLifeSpan(2.0f);

	}
}

float ABatteryPickup::GetPower()
{

	return BatteryPower;
}
