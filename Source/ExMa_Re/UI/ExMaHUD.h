// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ExMa_Re/Components/InventoryComponent.h"
#include "ExMaHUD.generated.h"

class UMainInteractionWidget;
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
	void InitInteractionWidget(UInventoryComponent* InInventoryComponentRef, UInventoryComponent* InOutInventoryComponentRef);

	UFUNCTION(BlueprintCallable)
	void ToggleWidgetVisibility();

	//TODO: Rework this to hint factory because we will need different hints about picked items & NPC radio messages in future
	UFUNCTION(BlueprintCallable)
	void InitPickupHintWidget();

	UFUNCTION(BlueprintCallable)
	void TogglePickupHintVisibility();

	//TODO: Implement states of main interaction widget
	UFUNCTION(BlueprintCallable)
	void ChangeMainWidgetState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menus")
	TSubclassOf<UMainInteractionWidget> MainWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hints")
	TSubclassOf<UUserWidget> PickupHintClass;
	
	UMainInteractionWidget* MainWidgetRef;
	UUserWidget* PickupHintRef;
};
