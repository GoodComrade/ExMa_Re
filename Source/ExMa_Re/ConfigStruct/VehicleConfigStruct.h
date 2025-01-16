#pragma once

#include "VehicleConfigStruct.generated.h"

USTRUCT(BlueprintType)
struct FVehicleConfigStruct : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    /** Please add a variable description */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MaxHealth"))
    float MaxHealth = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Armor"))
    float Armor = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MaxCargo"))
    float MaxCargo = 0;
};