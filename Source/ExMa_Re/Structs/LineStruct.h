#pragma once

#include "CoreMinimal.h"
#include "LineStruct.generated.h"

USTRUCT(BlueprintType)
struct FLineStruct
{
    GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D End;
};