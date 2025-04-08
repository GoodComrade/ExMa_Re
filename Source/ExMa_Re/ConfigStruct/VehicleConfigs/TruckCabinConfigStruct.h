#pragma once

#include "TruckCabinConfigStruct.generated.h"

USTRUCT(BlueprintType)
struct FTruckCabinConfigStruct : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MaxHealth"))
    float MaxHealth = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Armor"))
    float Armor = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "GasTankSize"))
    float GasTankSize = 0;

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
    int32 Cost = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "BulletResistance"))
    float BulletResistance = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ExplosionResistance"))
    float ExplosionResistance = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "EnergyResistance"))
    float EnergyResistance = 0;
};