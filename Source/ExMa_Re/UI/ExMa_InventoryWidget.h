// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExMa_Re/Components/InventoryComponent.h"
#include "ExMa_InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class EXMA_RE_API UExMa_InventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;
    void SetPlayerController(APlayerController* InPlayerController);

    UFUNCTION()
    void SetInventoryComponentRef(UInventoryComponent* InInventoryComponentRef);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta = (ExposeOnSpawn = "true", InstanceEditable = "true"))
    UInventoryComponent* InventoryComponentRef;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta = (ExposeOnSpawn = "true", InstanceEditable = "true"))
    float TileSize;

private:
    UPROPERTY()
    APlayerController* PlayerController;

    
};
