// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ExMa_Re/Components/InventoryComponent.h"
#include "ExMa_Re/Components/WeaponComponent.h"
#include "ExMa_Re/Weapons/WeaponSlot.h"

#include "ExMa_Re/Game/ExMa_RePlayerController.h"

#include "ExMaHUD.generated.h"

class UMainInteractionWidget;
class AExMa_GameState;
class AExMa_RePawn;

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
	void InitInteractionWidget(AExMa_RePawn* TargetVehicle, AExMa_RePlayerController* TargetPlayerController);

	UFUNCTION(BlueprintCallable)
	void ToggleWidgetVisibility(bool bIsEnbale);

	//TODO: Rework this to hint factory because we will need different hints about picked items & NPC radio messages in future
	UFUNCTION(BlueprintCallable)
	void InitPickupHintWidget(AExMa_RePlayerController* TargetPlayerController);

	UFUNCTION(BlueprintCallable)
	void TogglePickupHintVisibility(bool bNewState);

	//TODO: Implement states of main interaction widget
	UFUNCTION(BlueprintCallable)
	void ChangeMainWidgetState();

	UFUNCTION(BlueprintCallable)
	void ProcessDestroyMainWidget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menus")
	TSubclassOf<UMainInteractionWidget> MainWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hints")
	TSubclassOf<UUserWidget> PickupHintClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dev")
	TSubclassOf<UUserWidget> DevConsoleClass;
	
	UPROPERTY()
	UMainInteractionWidget* MainWidgetRef;

	UPROPERTY()
	UUserWidget* PickupHintRef;

	UPROPERTY()
	UUserWidget* DevConsoleRef;

private:
	AExMa_GameState* GetGameState();
};
