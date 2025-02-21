// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ExMaHUD.h"
#include "ExMa_Re/Components/InventoryComponent.h"
#include "ExMa_Re/UI/ExMa_InventoryWidget.h"
#include "ExMa_Re/UI/MainInteractionWidget.h"

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

void AExMaHUD::InitInteractionWidget(UInventoryComponent* InInventoryComponentRef, UInventoryComponent* InOutInventoryComponentRef)
{
    MainWidgetRef = CreateWidget<UMainInteractionWidget>(GetOwningPlayerController(), MainWidgetClass);

    if (MainWidgetRef)
    {
        MainWidgetRef->SetPlayerController(GetOwningPlayerController());
        MainWidgetRef->SetInventoryComponentRef(InInventoryComponentRef);
        MainWidgetRef->SetOutInventoryComponentRef(InOutInventoryComponentRef);
    }
}

void AExMaHUD::ToggleWidgetVisibility()
{
    if (MainWidgetRef->IsInViewport())
    {
        MainWidgetRef->RemoveFromParent();

        FInputModeGameOnly InputMode;
        GetOwningPlayerController()->SetInputMode(InputMode);
        GetOwningPlayerController()->SetShowMouseCursor(false);
    }
    else
    {
        MainWidgetRef->AddToViewport();

        FInputModeGameAndUI InputMode;
        InputMode.SetWidgetToFocus(MainWidgetRef->TakeWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        InputMode.SetHideCursorDuringCapture(false);

        GetOwningPlayerController()->SetInputMode(InputMode);
        GetOwningPlayerController()->SetShowMouseCursor(true);
    }
}

//TODO: Rework this to hint factory because we will need different hints about picked items & NPC radio messages in future
void AExMaHUD::InitPickupHintWidget()
{
    PickupHintRef = CreateWidget<UUserWidget>(GetOwningPlayerController(), PickupHintClass);
}

void AExMaHUD::TogglePickupHintVisibility(bool bNewState)
{
    if (bNewState)
        PickupHintRef->AddToViewport();
    else
        PickupHintRef->RemoveFromParent();
}

void AExMaHUD::ChangeMainWidgetState()
{
}
