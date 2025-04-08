#pragma once

#include "ExMa_Re/Structs/TileStruct.h"
#include "ExMa_Re/DataAssets/Vehicles/VehicleParts/Car/CarBodyDataAsset.h"
#include "CarBodyConfigStruct.generated.h"

USTRUCT(BlueprintType)
struct FCarBodyConfigStruct : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Health"))
    float MaxHealth = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Armor"))
    float MaxArmor = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "GasTankSize"))
    float GasTankSize = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "TrunkSize"))
    FTileStruct TrunkSize;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MaxTorque"))
    float MaxTorque = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MaxRPM"))
    float MaxRPM = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "EngineIdleRPM"))
    float EngineIdleRPM = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "EngineBrakeEffect"))
    float EngineBrakeEffect = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "EngineRPMSpeedup"))
    float EngineRPMSpeedup = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "EngineRPMSpeedup"))
    float EngineRPMSlowdown = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ChassisHeight"))
    float ChassisHeight = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "DragCoefficient"))
    float DragCoefficient = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "DownforceCoefficient"))
    float DownforceCoefficient = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "TopSpeed"))
    float TopSpeed = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "EnginePower"))
    float EnginePower = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Weight"))
    float Weight = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Cost"))
    float Cost = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "BulletResistance"))
    float BulletResistance = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ExplosionResistance"))
    float ExplosionResistance = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "EnergyResistance"))
    float EnergyResistance = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "VehicleUpgradeSlots"))
    TArray<FTileStruct> VehicleUpgradeSlots;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "VehicleReinforceSlots"))
    TArray<FTileStruct> VehicleReinforceSlots;

    //PROPERTY ONLY FOR CONCEPTION TESTS
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "WeaponSlots"))
    TArray<FTileStruct> WeaponSlots;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "CarBodyData"))
    UCarBodyDataAsset* CarBodyData;

};