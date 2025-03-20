#pragma once

#include "ItemType.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    Weapon              UMETA(DisplayName = "Weapon"),
    Cargo               UMETA(DisplayName = "Cargo"),
    VehicleUpgrade      UMETA(DisplayName = "VehicleUpgrade"),
    VehicleReinforce    UMETA(DisplayName = "VehicleReinforce"),
    None                UMETA(DisplayName = "NONE")
};