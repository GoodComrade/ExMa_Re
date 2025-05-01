// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ExMaHUD.h"

#include "ExMa_Re/Components/InventoryComponent.h"
#include "ExMa_Re/Components/WeaponComponent.h"

#include "ExMa_Re/UI/ExMa_InventoryWidget.h"
#include "ExMa_Re/UI/ExMa_WeaponSlotWidget.h"
#include "ExMa_Re/UI/MainInteractionWidget.h"

#include "ExMa_Re/Game/ExMa_GameState.h"
#include "ExMa_Re/Game/ExMa_RePlayerController.h"

#include "ExMa_Re/Vehicles/ExMa_RePawn.h"

AExMaHUD::AExMaHUD()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AExMaHUD::BeginPlay()
{
    Super::BeginPlay();

    DevConsoleRef = CreateWidget<UUserWidget>(GetOwningPlayerController(), DevConsoleClass);
    DevConsoleRef->AddToViewport();

    TogglePickupHintVisibility(false);
}

void AExMaHUD::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    //ShowInGameUI();
}

AExMa_GameState* AExMaHUD::GetGameState()
{
    UWorld* World = GetWorld();

    if(World == nullptr)
        return nullptr;

    AExMa_GameState* GameState = World->GetGameState<AExMa_GameState>();

    if(GameState == nullptr)
        return nullptr;

    return GameState;
}

void AExMaHUD::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AExMaHUD::InitInteractionWidget(AExMa_RePawn* TargetVehicle, AExMa_RePlayerController* TargetPlayerController)
{
    if (!TargetVehicle || !MainWidgetClass) return;

    if (MainWidgetRef)
    {
        MainWidgetRef->RemoveFromParent();
        MainWidgetRef = nullptr;
    }

    MainWidgetRef = CreateWidget<UMainInteractionWidget>(TargetPlayerController, MainWidgetClass);

    if (MainWidgetRef)
    {
        MainWidgetRef->SetPlayerController(TargetPlayerController);
        MainWidgetRef->SetInventoryComponentRef(TargetVehicle->GetInventoryComponent());
        MainWidgetRef->SetOutInventoryComponentRef(TargetVehicle->GetOutInventoryComponent());
        MainWidgetRef->SetWeaponComponentRef(TargetVehicle->GetWeaponComponent());

        //MainWidgetRef->InvalidateLayoutAndVolatility();
        //if (TSharedPtr<SWidget> SlateMainWidget = MainWidgetRef->GetCachedWidget())
        //{
        //    SlateMainWidget->SlatePrepass();
        //    SlateMainWidget->Invalidate(EInvalidateWidgetReason::LayoutAndVolatility);
        //}
        
        MainWidgetRef->OnVehicleChanged();

        MainWidgetRef->AddToViewport();
        MainWidgetRef->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void AExMaHUD::ToggleWidgetVisibility(bool bIsEnbale)
{
    if (bIsEnbale == false)
    {
        MainWidgetRef->SetVisibility(ESlateVisibility::Collapsed);

        FInputModeGameOnly InputMode;
        GetOwningPlayerController()->SetInputMode(InputMode);
        GetOwningPlayerController()->SetShowMouseCursor(false);
        UE_LOG(LogTemp, Error, TEXT("AExMaHUD::ToggleWidgetVisibility MainWidgetRef IS Collapsed & ImputMode is GameOnly!"));
    }
    else
    {
        MainWidgetRef->SetVisibility(ESlateVisibility::Visible);

        FInputModeGameAndUI InputMode;
        InputMode.SetWidgetToFocus(MainWidgetRef->TakeWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        InputMode.SetHideCursorDuringCapture(false);

        GetOwningPlayerController()->SetInputMode(InputMode);
        GetOwningPlayerController()->SetShowMouseCursor(true);

        UE_LOG(LogTemp, Error, TEXT("AExMaHUD::ToggleWidgetVisibility MainWidgetRef IS Visible & ImputMode is GameAndUI!"));
    }

    if (GetGameState() == nullptr)
        return;

    GetGameState()->SetGamePause(bIsEnbale);
}

//TODO: Rework this to hint factory because we will need different hints about picked items & NPC radio messages in future
void AExMaHUD::InitPickupHintWidget(AExMa_RePlayerController* TargetPlayerController)
{
    if (PickupHintRef)
    {
        PickupHintRef->RemoveFromParent();
        PickupHintRef = nullptr;
    }

    PickupHintRef = CreateWidget<UUserWidget>(TargetPlayerController, PickupHintClass);

    if (PickupHintRef)
    {
        PickupHintRef->AddToViewport();
        PickupHintRef->SetVisibility(ESlateVisibility::Collapsed);
    }
    //PickupHintRef->InvalidateLayoutAndVolatility();
    //if (TSharedPtr<SWidget> SlatePickupWidget = PickupHintRef->GetCachedWidget())
    //{
    //    SlatePickupWidget->SlatePrepass();
    //    SlatePickupWidget->Invalidate(EInvalidateWidgetReason::LayoutAndVolatility);
    //}
}

void AExMaHUD::TogglePickupHintVisibility(bool bNewState)
{
    if (PickupHintRef == nullptr)
        return;

    if (bNewState)
        PickupHintRef->SetVisibility(ESlateVisibility::Visible);
    else
        PickupHintRef->SetVisibility(ESlateVisibility::Collapsed);
}

void AExMaHUD::ChangeMainWidgetState()
{
}

void AExMaHUD::ProcessDestroyMainWidget()
{
}
