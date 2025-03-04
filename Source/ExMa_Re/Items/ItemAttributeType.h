#pragma once

#include "CoreMinimal.h"
#include "ItemAttributeType.generated.h"

UENUM()
enum class EItemAttributeType : uint8
{
    Health = 0                                      UMETA(DisplayName = "Health"),
    MaxHealth = 1                                   UMETA(DisplayName = "MaxHealth"),
    Type = 2                                        UMETA(DisplayName = "Type"),
    Weight = 3                                      UMETA(DisplayName = "Weight"),
    Cost = 4                                        UMETA(DisplayName = "Cost"),
};