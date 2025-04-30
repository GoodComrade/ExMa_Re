// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/VehicleSpawner.h"

#include "ExMa_Re/ConfigStruct/VehicleConfigs/VehicleConfigStruct.h"
#include "ExMa_Re/ConfigStruct/VehicleConfigs/CarBodyConfigStruct.h"
#include "ExMa_Re/ConfigStruct/VehicleConfigs/TruckCabinConfigStruct.h"
#include "ExMa_Re/ConfigStruct/VehicleConfigs/TruckBodyConfigStruct.h"

#include "ExMa_Re/ConfigStruct/WeaponConfigStruct.h"

#include "ExMa_Re/Game/ExMa_GameState.h"

// Sets default values
AVehicleSpawner::AVehicleSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVehicleSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnVehicles();
}

// Called every frame
void AVehicleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVehicleSpawner::SpawnVehicles()
{
	if (VehiclesToSpawn.Num() <= 0)
		return;

	AExMa_GameState* GameState = GetWorld()->GetGameState<AExMa_GameState>();

	if (GameState == nullptr)
		return;

	for (FSpawnableProperties SpawnProps : VehiclesToSpawn)
	{
		FVehicleConfigStruct* VehicleConfig = VehicleDT->FindRow<FVehicleConfigStruct>(SpawnProps.VehicleBase, "");

		FCarBodyConfigStruct* VehicleCarBodyConfig = VehicleCarBodyDT->FindRow<FCarBodyConfigStruct>(SpawnProps.VehicleBody, "");

		FTruckCabinConfigStruct* VehicleTruckCabinConfig = VehicleTruckCabinDT->FindRow<FTruckCabinConfigStruct>(SpawnProps.VehicleCabin, "");
		FTruckBodyConfigStruct* VehicleTruckBodyConfig = VehicleTruckBodyDT->FindRow<FTruckBodyConfigStruct>(SpawnProps.VehicleBody, "");

		FWeaponConfigStruct* WeaponConfig = WeaponDT->FindRow<FWeaponConfigStruct>(SpawnProps.VehicleWeapon, "");

		if (!VehicleConfig)
		{
			UE_LOG(LogTemp, Error, TEXT("AVehicleSpawner::SpawnVehicles: VehicleConfig NOT FOUND!"));
			return;
		}

		if (VehicleTruckCabinConfig)
		{
			if(!VehicleTruckBodyConfig)
			{
				UE_LOG(LogTemp, Error, TEXT("AVehicleSpawner::SpawnVehicles: VehicleTruckBodyConfig NOT FOUND!"));
				return;
			}

			GameState->SpawnTruckNPC(*VehicleConfig, *VehicleTruckCabinConfig, *VehicleTruckBodyConfig, SpawnProps.VehicleWeapon, ItemDT, WeaponDT, GetActorLocation());
		}
		else
		{
			if (!VehicleCarBodyConfig)
			{
				UE_LOG(LogTemp, Error, TEXT("AVehicleSpawner::SpawnVehicles: VehicleTruckBodyConfig NOT FOUND!"));
				return;
			}

			GameState->SpawnCarNPC(*VehicleConfig, *VehicleCarBodyConfig, SpawnProps.VehicleWeapon, ItemDT, WeaponDT, GetActorLocation());
		}
	}
}

