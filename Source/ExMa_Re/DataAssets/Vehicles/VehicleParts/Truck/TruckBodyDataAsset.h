// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/Vehicles/VehicleParts/VehiclePartDataAsset.h"
#include "TruckBodyDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class EXMA_RE_API UTruckBodyDataAsset : public UVehiclePartDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FTileStruct TrunkSize;
};
