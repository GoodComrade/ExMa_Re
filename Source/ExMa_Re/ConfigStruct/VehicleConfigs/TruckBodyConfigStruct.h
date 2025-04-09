#pragma once

#include "ExMa_Re/Structs/TileStruct.h"
#include "ExMa_Re/DataAssets/Vehicles/VehicleParts/Truck/TruckBodyDataAsset.h"
#include "TruckBodyConfigStruct.generated.h"

USTRUCT(BlueprintType)
struct FTruckBodyConfigStruct : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MaxHealth"))
    float MaxHealth = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Armor"))
    float MaxArmor = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "TrunkSize"))
    FTileStruct TrunkSize;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Weight"))
    float Weight = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Cost"))
    int32 Cost = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "BulletResistance"))
    float BulletResistance = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ExplosionResistance"))
    float ExplosionResistance = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "EnergyResistance"))
    float EnergyResistance = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "WeaponSlots"))
    TArray<FTileStruct> WeaponSlots;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "TruckBodyData"))
    UTruckBodyDataAsset* TruckBodyData;
};