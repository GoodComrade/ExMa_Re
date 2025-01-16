#pragma once

#include "ItemConfigStruct.generated.h"

USTRUCT(BlueprintType)
struct FItemConfigStruct : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    /** Please add a variable description */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MaxHealth"))
    float MaxHealth = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Size"))
    float Size = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Type"))
    float Type = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Weight"))
    float Weight = 0;
};