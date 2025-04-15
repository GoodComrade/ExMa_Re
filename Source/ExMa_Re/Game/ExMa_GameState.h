// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ExMa_Re/Items/ItemObject.h"
#include "ExMa_Re/ConfigStruct/ItemConfigStruct.h"
#include "ExMa_Re/ConfigStruct/WeaponConfigStruct.h"

#include "ExMa_Re/ConfigStruct/VehicleConfigs/VehicleConfigStruct.h"
#include "ExMa_Re/ConfigStruct/VehicleConfigs/CarBodyConfigStruct.h"
#include "ExMa_Re/ConfigStruct/VehicleConfigs/TruckCabinConfigStruct.h"
#include "ExMa_Re/ConfigStruct/VehicleConfigs/TruckBodyConfigStruct.h"

#include "ExMa_GameState.generated.h"

class UItemObject;
class UWeaponItemObject;
class AActor;
class AChestActor;
class UInventoryComponent;
class AExMa_RePawn;

class UVehicleDataAsset;
class UVehiclePartDataAsset;

class UCarBodyDataAsset;

class UTruckCabinDataAsset;
class UTruckBodyDataAsset;

UCLASS()
class EXMA_RE_API AExMa_GameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SpawnCrateActorFromPawn(TSubclassOf<AChestActor> ItemActorToSpawn, UInventoryComponent* InventoryToCopy, AActor* ActorFromSpawn, bool GroundClamp);

	UFUNCTION(BlueprintCallable)
	void SetGamePause(bool bIsPause);

	UFUNCTION(BlueprintCallable)
	UItemObject* CreateItem(FName TargetItemName, UDataTable* ItemsDT, UDataTable* WeaponsDT);

public:

	UFUNCTION(BlueprintCallable)
	void SpawnCarPawn(FVehicleConfigStruct TargetVehicleConfigRow, FCarBodyConfigStruct TargetCarBodyConfigRow);

	UFUNCTION(BlueprintCallable)
	void SpawnTruckPawn(FVehicleConfigStruct TargetVehicleConfigRow, FTruckCabinConfigStruct TargetTruckCabinConfigRow, FTruckBodyConfigStruct TargetTruckBodyConfigRow);

private:
	UWeaponItemObject* CreateWeaponItem(FItemConfigStruct TargetItemRow, FName TargetWeaponName, UDataTable* WeaponsDT);

	UVehicleDataAsset* MakeVehicleDataAsset(FVehicleConfigStruct TargetVehicleConfigRow);

	UCarBodyDataAsset* MakeCarBodyDataAsset(FCarBodyConfigStruct TargetCarBodyConfigRow);

	UTruckCabinDataAsset* MakeTruckCabinDataAsset(FTruckCabinConfigStruct TargetTruckCabinConfigRow);
	UTruckBodyDataAsset* MakeTruckBodyDataAsset(FTruckBodyConfigStruct TargetTruckBodyConfigRow);

	AExMa_RePawn* CreateAndPossessVehicle(UVehicleDataAsset* VehicleData, APlayerController* PlayerController, AExMa_RePawn* PossessedPawn, FVector PlayerPawnLocation, UWorld* World);

	AVehiclePart* CreateVehiclePart(UVehiclePartDataAsset* TargetData, AExMa_RePawn* OwnerPawn, FVector PlayerPawnLocation, UWorld* World);

};
