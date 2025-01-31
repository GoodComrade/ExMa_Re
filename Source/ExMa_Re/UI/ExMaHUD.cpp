// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ExMaHUD.h"
#include "ExMa_Re/Components/InventoryComponent.h"
#include "ExMa_Re/UI/ExMa_InventoryWidget.h"

AExMaHUD::AExMaHUD()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AExMaHUD::BeginPlay()
{
    Super::BeginPlay();
}

void AExMaHUD::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    //ShowInGameUI();
}

void AExMaHUD::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AExMaHUD::InitInventoryWidget(UInventoryComponent* InInventoryComponentRef)
{
    InventoryWidgetRef = CreateWidget<UExMa_InventoryWidget>(GetOwningPlayerController(), InventoryWidgetclass);
    if (InventoryWidgetRef)
    {
        InventoryWidgetRef->SetPlayerController(GetOwningPlayerController());
        InventoryWidgetRef->SetInventoryComponentRef(InInventoryComponentRef);
    }
}

void AExMaHUD::ToggleInventoryVisibility()
{
    if (InventoryWidgetRef->IsInViewport())
    {
        InventoryWidgetRef->RemoveFromParent();

        FInputModeGameOnly InputMode;
        GetOwningPlayerController()->SetInputMode(InputMode);
        GetOwningPlayerController()->SetShowMouseCursor(false);
    }
    else
    {
        InventoryWidgetRef->AddToViewport();

        FInputModeGameAndUI InputMode;
        InputMode.SetWidgetToFocus(InventoryWidgetRef->TakeWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        InputMode.SetHideCursorDuringCapture(false);

        GetOwningPlayerController()->SetInputMode(InputMode);
        GetOwningPlayerController()->SetShowMouseCursor(true);
    }
}
