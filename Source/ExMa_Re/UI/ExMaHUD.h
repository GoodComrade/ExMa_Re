// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ExMa_Re/Components/InventoryComponent.h"
#include "ExMaHUD.generated.h"

class UExMa_InventoryWidget;

UCLASS()
class EXMA_RE_API AExMaHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AExMaHUD();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void InitInventoryWidget(UInventoryComponent* InInventoryComponentRef);

	UFUNCTION(BlueprintCallable)
	void ToggleInventoryVisibility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menus")
	TSubclassOf<UExMa_InventoryWidget> InventoryWidgetclass;
	
	UExMa_InventoryWidget* InventoryWidgetRef;
};
