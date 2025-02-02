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
	UFUNCTION()
	FVector2D GetDimentions() const { return Dimensions; }

	UFUNCTION(BlueprintCallable)
	UMaterialInterface* GetIcon() const { return IsRotated ? IconRotated : Icon; }

	UFUNCTION()
	void SetDimentions(int DimentionX, int DimentionY);

	UFUNCTION()
	void SetIcons(UMaterialInterface* InIcon, UMaterialInterface* InIconRotated);

	UFUNCTION(BlueprintCallable)
	void SetItemActorClass(TSubclassOf<AItemActor> InItemActorClass);

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	FVector2D Dimensions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	UMaterialInterface* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	UMaterialInterface* IconRotated;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	TSubclassOf<AItemActor> ItemActorClass;

	UPROPERTY()
	bool IsRotated;
};
