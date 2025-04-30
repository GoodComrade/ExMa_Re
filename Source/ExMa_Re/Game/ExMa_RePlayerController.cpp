// Copyright Epic Games, Inc. All Rights Reserved.


#include "ExMa_RePlayerController.h"
#include "ExMa_Re/Vehicles/ExMa_RePawn.h"
#include "ExMa_Re/UI/ExMa_ReUI.h"
#include "EnhancedInputSubsystems.h"
#include "ChaosWheeledVehicleMovementComponent.h"

void AExMa_RePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// spawn the UI widget and add it to the viewport
	VehicleUI = CreateWidget<UExMa_ReUI>(this, VehicleUIClass);

	check(VehicleUI);

	VehicleUI->AddToViewport();
}

void AExMa_RePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		// optionally add the steering wheel context
		if (bUseSteeringWheelControls && SteeringWheelInputMappingContext)
		{
			Subsystem->AddMappingContext(SteeringWheelInputMappingContext, 1);
		}
	}
}

void AExMa_RePlayerController::Tick(float Delta)
{
	Super::Tick(Delta);

	if (IsValid(VehiclePawn) && IsValid(VehicleUI))
	{
		VehicleUI->UpdateSpeed(VehiclePawn->GetChaosVehicleMovement()->GetForwardSpeed());
		VehicleUI->UpdateGear(VehiclePawn->GetChaosVehicleMovement()->GetCurrentGear());
	}
}

void AExMa_RePlayerController::UpdateHUDWithNewVehicle(AExMa_RePawn* InVehicle)
{
	if (!InVehicle)
		return;

	if(!HUD)
		HUD = Cast<AExMaHUD>(GetHUD());

	if (HUD)
	{
		HUD->InitInteractionWidget(InVehicle);
		HUD->InitPickupHintWidget();
	}
}


void AExMa_RePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// get a pointer to the controlled pawn
	VehiclePawn = CastChecked<AExMa_RePawn>(InPawn);

	if (VehiclePawn)
		UpdateHUDWithNewVehicle(VehiclePawn);
}
