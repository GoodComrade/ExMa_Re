// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/Vehicles/VehicleParts/VehiclePartDataAsset.h"
#include "TruckCabinDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class EXMA_RE_API UTruckCabinDataAsset : public UVehiclePartDataAsset
{
	GENERATED_BODY()
	
public:
    UTruckCabinDataAsset(const FObjectInitializer& ObjectInitializer);

public:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float GasTankSize = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float MaxTorque = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float MaxRPM = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float EngineIdleRPM = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float EngineBrakeEffect = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float EngineRPMSpeedup = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float EngineRPMSlowdown = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float ChassisHeight = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float DragCoefficient = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float DownforceCoefficient = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float TopSpeed = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float EnginePower = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TArray<FTileStruct> VehicleUpgradeSlots;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TArray<FTileStruct> VehicleReinforceSlots;
};
