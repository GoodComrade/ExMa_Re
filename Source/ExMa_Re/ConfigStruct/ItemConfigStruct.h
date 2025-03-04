#pragma once

#include "Materials/MaterialInterface.h"
#include "ItemConfigStruct.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    Weapon              UMETA(DisplayName = "Weapon"),
    Cargo               UMETA(DisplayName = "Cargo"),
    VehicleUpgrade      UMETA(DisplayName = "VehicleUpgrade"),
    None                UMETA(DisplayName = "NONE")
};

USTRUCT(BlueprintType)
struct FItemConfigStruct : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ItemType"))
    EItemType ItemType = EItemType::None;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MaxHealth"))
    float MaxHealth = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Weight"))
    float Weight = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Cost", EditCondition = "ItemType == EItemType::Weapon"))
    float Cost = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "SizeX"))
    float SizeX = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "SizeX"))
    float SizeY = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Type"))
    UMaterialInterface* Icon;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Weight"))
    UMaterialInterface* IconRotated;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ItemType"))
    FString Description;
};