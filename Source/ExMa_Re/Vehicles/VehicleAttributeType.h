#pragma once

#include "CoreMinimal.h"
#include "VehicleAttributeType.generated.h"

UENUM()
enum class EVehicleAttributeType : uint8
{
    Health = 0                                      UMETA(DisplayName = "Health"),
    MaxHealth = 1                                   UMETA(DisplayName = "MaxHealth"),
    Armor = 2                                       UMETA(DisplayName = "Armor"),
    GasTankSize = 3                                 UMETA(DisplayName = "GasTankSize"),
    TrankSize = 4                                   UMETA(DisplayName = "TrankSize"),
    MaxTorque = 5                                   UMETA(DisplayName = "MaxTorque"),
    MaxRPM = 6                                      UMETA(DisplayName = "MaxRPM"),
    EngineIdleRPM = 7                               UMETA(DisplayName = "EngineIdleRPM"),
    EngineBrakeEffect = 8                           UMETA(DisplayName = "EngineBrakeEffect"),
    EngineRPMSpeedup = 9                            UMETA(DisplayName = "EngineRPMSpeedup"),
    EngineRPMSlowdown = 10                          UMETA(DisplayName = "EngineRPMSlowdown"),
    ChassisHeight = 11                              UMETA(DisplayName = "ChassisHeight"),
    DragCoefficient = 12                            UMETA(DisplayName = "DragCoefficient"),
    DownforceCoefficient = 13                       UMETA(DisplayName = "DownforceCoefficient"),
    TopSpeed = 14                                   UMETA(DisplayName = "TopSpeed"),
    EnginePower = 15                                UMETA(DisplayName = "EnginePower"),
    Weight = 16                                     UMETA(DisplayName = "Weight"),
    BulletResistance = 17                           UMETA(DisplayName = "BulletResistance"),
    ExplosionResistance = 18                        UMETA(DisplayName = "ExplosionResistance"),
    EnergyResistance = 19                           UMETA(DisplayName = "EnergyResistance"),
};