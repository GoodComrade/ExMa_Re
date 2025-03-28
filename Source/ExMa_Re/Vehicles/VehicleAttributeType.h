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
    MaxTorque = 4                                   UMETA(DisplayName = "MaxTorque"),
    MaxRPM = 5                                      UMETA(DisplayName = "MaxRPM"),
    EngineIdleRPM = 6                               UMETA(DisplayName = "EngineIdleRPM"),
    EngineBrakeEffect = 7                           UMETA(DisplayName = "EngineBrakeEffect"),
    EngineRPMSpeedup = 8                            UMETA(DisplayName = "EngineRPMSpeedup"),
    EngineRPMSlowdown = 9                          UMETA(DisplayName = "EngineRPMSlowdown"),
    ChassisHeight = 10                              UMETA(DisplayName = "ChassisHeight"),
    DragCoefficient = 11                            UMETA(DisplayName = "DragCoefficient"),
    DownforceCoefficient = 12                       UMETA(DisplayName = "DownforceCoefficient"),
    TopSpeed = 13                                   UMETA(DisplayName = "TopSpeed"),
    EnginePower = 14                                UMETA(DisplayName = "EnginePower"),
    Weight = 15                                     UMETA(DisplayName = "Weight"),
    BulletResistance = 16                           UMETA(DisplayName = "BulletResistance"),
    ExplosionResistance = 17                        UMETA(DisplayName = "ExplosionResistance"),
    EnergyResistance = 18                           UMETA(DisplayName = "EnergyResistance"),
};