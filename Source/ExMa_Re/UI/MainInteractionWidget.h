// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExMa_Re/Components/InventoryComponent.h"
#include "MainInteractionWidget.generated.h"


UCLASS()
class EXMA_RE_API UMainInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;

#pragma region PlayerComponents
    UFUNCTION(BlueprintCallable)
    void SetPlayerController(APlayerController* InPlayerController);
    UFUNCTION(BlueprintCallable)
    void SetInventoryComponentRef(UInventoryComponent* InInventoryComponentRef);
    UFUNCTION(BlueprintCallable)
    void SetOutInventoryComponentRef(UInventoryComponent* InOutInventoryComponentRef);
#pragma endregion Setters

#pragma region PlayerComponents
    UFUNCTION(BlueprintCallable, BlueprintPure)
    APlayerController* GetPlayerControllerComponent() const { return PlayerController; };

    UFUNCTION(BlueprintCallable, BlueprintPure)
    UInventoryComponent* GetInventoryComponentRef() const { return InventoryComponentRef; };

    UFUNCTION(BlueprintCallable, BlueprintPure)
    UInventoryComponent* GetOutInventoryComponent() const { return OutInventoryComponent; };
#pragma endregion Getters

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta = (ExposeOnSpawn = "true", InstanceEditable = "true"))
    UInventoryComponent* InventoryComponentRef;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta = (ExposeOnSpawn = "true", InstanceEditable = "true"))
    UInventoryComponent* OutInventoryComponent;

    UPROPERTY()
    APlayerController* PlayerController;
};
