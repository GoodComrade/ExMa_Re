#pragma once

#include "Materials/MaterialInterface.h"
#include "ItemConfigStruct.generated.h"

USTRUCT(BlueprintType)
struct FItemConfigStruct : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    /** Please add a variable description */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MaxHealth"))
    float MaxHealth = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "SizeX"))
    float SizeX = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "SizeX"))
    float SizeY = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Type"))
    UMaterialInterface* Icon;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Weight"))
    UMaterialInterface* IconRotated;
};