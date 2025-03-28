#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "VehicleType.generated.h"

UENUM(BlueprintType)
enum class EVehicleType : uint8
{
    CAR = 0 UMETA(DisplayName = "Car"),
    TRUCK = 1 UMETA(DisplayName = "Truck"),
    NONE = 2 UMETA(DisplayName = "None")
};