#pragma once

#include "TileStruct.generated.h"

USTRUCT(BlueprintType)
struct FTileStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Y;
};