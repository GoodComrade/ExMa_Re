#pragma once

#include "ExMa_Re/Enums/VehicleType.h"
#include "ExMa_Re/DataAssets/Vehicles/VehicleDataAsset.h"
#include "VehicleConfigStruct.generated.h"

USTRUCT(BlueprintType)
struct FVehicleConfigStruct : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "VehicleType"))
    EVehicleType VehicleType = EVehicleType::NONE;

    /** Please add a variable description */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MaxHealth"))
    float MaxHealth = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MaxArmor"))
    float MaxArmor = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Weight"))
    float Weight = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MaxWeight"))
    float MaxWeight = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "BulletResistance"))
    float BulletResistance = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ExplosionResistance"))
    float ExplosionResistance = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "EnergyResistance"))
    float EnergyResistance = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Cost"))
    int32 Cost = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "EnergyResistance"))
    UVehicleDataAsset* VehicleData;
};