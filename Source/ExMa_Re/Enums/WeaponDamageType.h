#pragma once

#include "WeaponDamageType.generated.h"

UENUM(BlueprintType)
enum class EWeaponDamageType : uint8
{
    Bullet               UMETA(DisplayName = "Bullet"),
    Energy               UMETA(DisplayName = "Energy"),
    Explosive            UMETA(DisplayName = "Explosive"),
    None                 UMETA(DisplayName = "NONE")
};