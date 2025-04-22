// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ExMaHUD.h"

#include "ExMa_Re/Components/InventoryComponent.h"
#include "ExMa_Re/Components/WeaponComponent.h"

#include "ExMa_Re/UI/ExMa_InventoryWidget.h"
#include "ExMa_Re/UI/ExMa_WeaponSlotWidget.h"
#include "ExMa_Re/UI/MainInteractionWidget.h"

#include "ExMa_Re/Game/ExMa_GameState.h"

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

void AExMaHUD::InitInteractionWidget(UInventoryComponent* InInventoryComponentRef, UInventoryComponent* InOutInventoryComponentRef, UWeaponComponent* InWeaponComponent)
{
    MainWidgetRef = CreateWidget<UMainInteractionWidget>(GetOwningPlayerController(), MainWidgetClass);

    if (MainWidgetRef)
    {
        MainWidgetRef->SetPlayerController(GetOwningPlayerController());
        MainWidgetRef->SetInventoryComponentRef(InInventoryComponentRef);
        MainWidgetRef->SetOutInventoryComponentRef(InOutInventoryComponentRef);
        MainWidgetRef->SetWeaponComponentRef(InWeaponComponent);

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
    }

    if (GetGameState() == nullptr)
        return;

    GetGameState()->SetGamePause(bIsEnbale);
}

//TODO: Rework this to hint factory because we will need different hints about picked items & NPC radio messages in future
void AExMaHUD::InitPickupHintWidget()
{
    PickupHintRef = CreateWidget<UUserWidget>(GetOwningPlayerController(), PickupHintClass);

    if (!PickupHintRef)
    {
		UE_LOG(LogTemp, Warning, TEXT("AExMaHUD::InitPickupHintWidget: PickupHintRef is nullptr"));
		return;
    }

    PickupHintRef->AddToViewport();
    PickupHintRef->SetVisibility(ESlateVisibility::Collapsed);
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
