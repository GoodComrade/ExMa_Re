#pragma once

#include "CoreMinimal.h"
#include "ItemAttributeType.generated.h"

UENUM()
enum class EItemAttributeType : uint8
{
    Health = 0                                      UMETA(DisplayName = "Health"),
    MaxHealth = 1                                   UMETA(DisplayName = "MaxHealth"),
    Size = 2                                      UMETA(DisplayName = "Size"),
    Type = 3                                   UMETA(DisplayName = "Type"),
    Weight = 4                                       UMETA(DisplayName = "Weight"),
};