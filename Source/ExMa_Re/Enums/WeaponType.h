#pragma once

#include "WeaponType.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    LightMachineGun              UMETA(DisplayName = "LightMachineGun"),
    MediumMachineGun             UMETA(DisplayName = "MediumMachineGun"),
    HeavyMachineGun              UMETA(DisplayName = "HeavyMachineGun"),
    Shotgun                      UMETA(DisplayName = "Shotgun"),
    PlasmaGun                    UMETA(DisplayName = "PlasmaGun"),
    LightArtilery                UMETA(DisplayName = "LightArtilery"),
    MediumArtilery               UMETA(DisplayName = "MediumArtilery"),
    HeavyArtilery                UMETA(DisplayName = "HeavyArtilery"),
    RocketLauncher               UMETA(DisplayName = "RocketLauncher"),
    SideRocketLauncher           UMETA(DisplayName = "SideRocketLauncher"),
    Canon                        UMETA(DisplayName = "Canon"),
    PlasmaCanon                  UMETA(DisplayName = "PlasmaGun"),
    None                         UMETA(DisplayName = "NONE")
};