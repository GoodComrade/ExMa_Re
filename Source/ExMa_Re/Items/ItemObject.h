// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Materials/MaterialInterface.h"
#include "ItemObject.generated.h"

class AItemActor;

UCLASS(Blueprintable, BlueprintType)
class EXMA_RE_API UItemObject : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	FVector2D GetDimentions() const { return bIsRotated ? FVector2D(Dimensions.Y, Dimensions.X) : Dimensions; };

	UFUNCTION(BlueprintCallable)
	UMaterialInterface* GetIcon() const { return bIsRotated ? IconRotated : Icon; }

	UFUNCTION(BlueprintCallable)
	TSubclassOf<class AItemActor> GetItemActorClass() const { return ItemActorClass; };

	UFUNCTION(BlueprintCallable)
	void SetDimentions(int DimentionX, int DimentionY);

	UFUNCTION(BlueprintCallable)
	void SetIcons(UMaterialInterface* InIcon, UMaterialInterface* InIconRotated);

	UFUNCTION(BlueprintCallable)
	void SetItemActorClass(TSubclassOf<AItemActor> InItemActorClass);

	UFUNCTION(BlueprintCallable)
	void Rotate();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsRotated() const { return bIsRotated; };

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	FVector2D Dimensions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	UMaterialInterface* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	UMaterialInterface* IconRotated;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	TSubclassOf<class AItemActor> ItemActorClass;

	UPROPERTY()
	bool bIsRotated;
};
