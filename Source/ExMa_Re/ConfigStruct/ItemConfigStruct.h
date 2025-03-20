#pragma once

#include "Materials/MaterialInterface.h"
#include "ExMa_Re/Enums/ItemType.h"
#include "ExMa_Re/DataAssets/ItemDataAsset.h"
#include "GameplayTagContainer.h"
#include "Engine/StaticMesh.h"
#include "GameplayTagContainer.h"
#include "ItemConfigStruct.generated.h"

//UENUM(BlueprintType)
//enum class EItemType : uint8
//{
//    Weapon              UMETA(DisplayName = "Weapon"),
//    Cargo               UMETA(DisplayName = "Cargo"),
//    VehicleUpgrade      UMETA(DisplayName = "VehicleUpgrade"),
//    None                UMETA(DisplayName = "NONE")
//};

USTRUCT(BlueprintType)
struct FItemConfigStruct : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ItemType"))
    FGameplayTagContainer ItemType;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "SizeX"))
    int SizeX = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "SizeY"))
    int SizeY = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Icon"))
    UMaterialInterface* Icon;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "IconRotated"))
    UMaterialInterface* IconRotated;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Description"))
    FString Description;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Weight"))
    int Weight = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Cost"))
    int Cost = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ItemData"))
    UItemDataAsset* ItemData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (DisplayName = "PreviewMesh"));
    UStaticMesh* PreviewMesh;
};