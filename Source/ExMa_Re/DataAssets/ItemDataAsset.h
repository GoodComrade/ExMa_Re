// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Engine/StaticMesh.h"
#include "ItemDataAsset.generated.h"

class UItemObject;

UCLASS(BlueprintType, Blueprintable)
class EXMA_RE_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Meta = (DefaultToSelf = "Outer"))
	static UItemObject* ConstructItemInstance(UItemDataAsset* ItemData);

public:
	UItemDataAsset(const FObjectInitializer& ObjectInitializer);

	virtual UItemObject* ConstructItemInstance();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (MultiLine = "true"));
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (MultiLine = "true"));
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	FGameplayTagContainer ItemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Weight = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Cost = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMesh* PreviewMesh;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UItemObject> ItemObjectClass;
};
