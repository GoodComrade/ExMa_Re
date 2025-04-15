// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExMa_Re/Weapons/WeaponSlot.h"
#include "ExMa_WeaponSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class EXMA_RE_API UExMa_WeaponSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UFUNCTION(BlueprintCallable)
    void SetComponents(APlayerController* InPlayerController, UWeaponSlot* InWeaponSlotRef);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta = (ExposeOnSpawn = "true", InstanceEditable = "true"))
    UWeaponSlot* WeaponSlotRef;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta = (ExposeOnSpawn = "true", InstanceEditable = "true"))
    float TileSize;

private:
    UPROPERTY()
    APlayerController* PlayerController;
};
