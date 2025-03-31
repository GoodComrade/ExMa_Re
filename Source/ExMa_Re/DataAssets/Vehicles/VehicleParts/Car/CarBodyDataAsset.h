// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/Vehicles/VehicleParts/VehiclePartDataAsset.h"
#include "CarBodyDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class EXMA_RE_API UCarBodyDataAsset : public UVehiclePartDataAsset
{
	GENERATED_BODY()
	
public:
    UCarBodyDataAsset(const FObjectInitializer& ObjectInitializer);

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
    float TopSpeed = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float EnginePower = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FTileStruct TrunkSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FTileStruct> VehicleUpgradeSlots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FTileStruct> VehicleReinforceSlots;
};
