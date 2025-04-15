// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExMa_Re/Components/InventoryComponent.h"
#include "ExMa_Re/Components/WeaponComponent.h"
#include "ExMa_Re/Weapons/WeaponSlot.h"
#include "MainInteractionWidget.generated.h"

class UWeaponSlot;

UCLASS()
class EXMA_RE_API UMainInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;

    UFUNCTION(BlueprintImplementableEvent)
    void OnWeaponSlotCreated(UWeaponSlot* CreatedSlot);

#pragma region PlayerComponents
    UFUNCTION(BlueprintCallable)
    void SetPlayerController(APlayerController* InPlayerController);

    UFUNCTION(BlueprintCallable)
    void SetInventoryComponentRef(UInventoryComponent* InInventoryComponentRef);

    UFUNCTION(BlueprintCallable)
    void SetOutInventoryComponentRef(UInventoryComponent* InOutInventoryComponentRef);

    UFUNCTION(BlueprintCallable)
    void SetWeaponComponentRef(UWeaponComponent* InWeaponComponenttRef);
#pragma endregion Setters

#pragma region PlayerComponents
    UFUNCTION(BlueprintCallable, BlueprintPure)
    APlayerController* GetPlayerControllerComponent() const { return PlayerController; };

    UFUNCTION(BlueprintCallable, BlueprintPure)
    UInventoryComponent* GetInventoryComponentRef() const { return InventoryComponentRef; };

    UFUNCTION(BlueprintCallable, BlueprintPure)
    UInventoryComponent* GetOutInventoryComponent() const { return OutInventoryComponentRef; };

    UFUNCTION(BlueprintCallable, BlueprintPure)
    UWeaponComponent* GetWeaponComponent() const { return WeaponComponentRef; };
#pragma endregion Getters

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta = (ExposeOnSpawn = "true", InstanceEditable = "true"))
    UInventoryComponent* InventoryComponentRef;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta = (ExposeOnSpawn = "true", InstanceEditable = "true"))
    UInventoryComponent* OutInventoryComponentRef;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta = (ExposeOnSpawn = "true", InstanceEditable = "true"))
    UWeaponComponent* WeaponComponentRef;

    UPROPERTY()
    APlayerController* PlayerController;

private:

    UFUNCTION()
    void OnSlotSelected(UWeaponSlot* CreatedSlot);
};
