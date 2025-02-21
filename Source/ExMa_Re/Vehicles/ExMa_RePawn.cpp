// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExMa_RePawn.h"
#include "ExMa_Re/Wheels/ExMa_ReWheelFront.h"
#include "ExMa_Re/Wheels/ExMa_ReWheelRear.h"
#include "ExMa_Re/Components/InventoryComponent.h"
#include "ExMa_Re/UI/ExMaHUD.h"
#include "ExMa_Re/Items/ItemActor.h"
#include "ExMa_Re/Items/ItemObject.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ExMa_VehicleAttributes.h"
#include "ChaosWheeledVehicleMovementComponent.h"

#define LOCTEXT_NAMESPACE "VehiclePawn"

DEFINE_LOG_CATEGORY(LogTemplateVehicle);

AExMa_RePawn::AExMa_RePawn()
{
	// construct the front camera boom
	FrontSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Front Spring Arm"));
	FrontSpringArm->SetupAttachment(GetMesh());
	FrontSpringArm->TargetArmLength = 0.0f;
	FrontSpringArm->bDoCollisionTest = false;
	FrontSpringArm->bEnableCameraRotationLag = true;
	FrontSpringArm->CameraRotationLagSpeed = 15.0f;
	FrontSpringArm->SetRelativeLocation(FVector(30.0f, 0.0f, 120.0f));

	FrontCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Front Camera"));
	FrontCamera->SetupAttachment(FrontSpringArm);
	FrontCamera->bAutoActivate = false;

	// construct the back camera boom
	BackSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Back Spring Arm"));
	BackSpringArm->SetupAttachment(GetMesh());
	BackSpringArm->TargetArmLength = 650.0f;
	BackSpringArm->SocketOffset.Z = 150.0f;
	BackSpringArm->bDoCollisionTest = false;
	BackSpringArm->bInheritPitch = false;
	BackSpringArm->bInheritRoll = false;
	BackSpringArm->bInheritYaw = false;
	BackSpringArm->bEnableCameraRotationLag = false;
	BackSpringArm->CameraRotationLagSpeed = 2.0f;
	BackSpringArm->CameraLagMaxDistance = 50.0f;

	BackCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Back Camera"));
	BackCamera->SetupAttachment(BackSpringArm);

	// Configure the car mesh
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(FName("Vehicle"));

	// get the Chaos Wheeled movement component
	ChaosVehicleMovement = CastChecked<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement());

	Attributes = CreateDefaultSubobject<UExMa_VehicleAttributes>(TEXT("AttributeSet"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	OutInventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("OutInventoryComponent"));

	CollectSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectSphere"));
	CollectSphere->SetupAttachment(GetMesh());

	CollectSphere->OnComponentBeginOverlap.AddDynamic(this, &AExMa_RePawn::OnCollectSphereBeginOverlap);
	CollectSphere->OnComponentEndOverlap.AddDynamic(this, &AExMa_RePawn::OnCollectSphereEndOverlap);

}

void AExMa_RePawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// steering 
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &AExMa_RePawn::Steering);
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Completed, this, &AExMa_RePawn::Steering);

		// throttle 
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &AExMa_RePawn::Throttle);
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &AExMa_RePawn::Throttle);

		// break 
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &AExMa_RePawn::Brake);
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Started, this, &AExMa_RePawn::StartBrake);
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Completed, this, &AExMa_RePawn::StopBrake);

		// handbrake 
		EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Started, this, &AExMa_RePawn::StartHandbrake);
		EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Completed, this, &AExMa_RePawn::StopHandbrake);

		// look around 
		EnhancedInputComponent->BindAction(LookAroundAction, ETriggerEvent::Triggered, this, &AExMa_RePawn::LookAround);

		// toggle camera 
		EnhancedInputComponent->BindAction(ToggleCameraAction, ETriggerEvent::Triggered, this, &AExMa_RePawn::ToggleCamera);
		
		// toggle inventory 
		EnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Triggered, this, &AExMa_RePawn::ToggleInventory);

		// reset the vehicle 
		EnhancedInputComponent->BindAction(ResetVehicleAction, ETriggerEvent::Triggered, this, &AExMa_RePawn::ResetVehicle);

	}
	else
	{
		UE_LOG(LogTemplateVehicle, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AExMa_RePawn::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<AExMaHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (HUD)
	{
		HUD->InitInteractionWidget(GetInventoryComponent(), GetOutInventoryComponent());
		HUD->InitPickupHintWidget();
	}

	SetupVehicleAttributes();
}

void AExMa_RePawn::Tick(float Delta)
{
	Super::Tick(Delta);

	// add some angular damping if the vehicle is in midair
	bool bMovingOnGround = ChaosVehicleMovement->IsMovingOnGround();
	GetMesh()->SetAngularDamping(bMovingOnGround ? 0.0f : 3.0f);

	// realign the camera yaw to face front
	//float CameraYaw = BackSpringArm->GetRelativeRotation().Yaw;
	//CameraYaw = FMath::FInterpTo(CameraYaw, 0.0f, Delta, 1.0f);
	//
	//BackSpringArm->SetRelativeRotation(FRotator(0.0f, CameraYaw, 0.0f));
}

void AExMa_RePawn::Steering(const FInputActionValue& Value)
{
	// get the input magnitude for steering
	float SteeringValue = Value.Get<float>();

	// add the input
	ChaosVehicleMovement->SetSteeringInput(SteeringValue);
}

void AExMa_RePawn::Throttle(const FInputActionValue& Value)
{
	// get the input magnitude for the throttle
	float ThrottleValue = Value.Get<float>();

	// add the input
	ChaosVehicleMovement->SetThrottleInput(ThrottleValue);
}

void AExMa_RePawn::Brake(const FInputActionValue& Value)
{
	// get the input magnitude for the brakes
	float BreakValue = Value.Get<float>();

	// add the input
	ChaosVehicleMovement->SetBrakeInput(BreakValue);
}

void AExMa_RePawn::StartBrake(const FInputActionValue& Value)
{
	// call the Blueprint hook for the break lights
	BrakeLights(true);
}

void AExMa_RePawn::StopBrake(const FInputActionValue& Value)
{
	// call the Blueprint hook for the break lights
	BrakeLights(false);

	// reset brake input to zero
	ChaosVehicleMovement->SetBrakeInput(0.0f);
}

void AExMa_RePawn::StartHandbrake(const FInputActionValue& Value)
{
	// add the input
	ChaosVehicleMovement->SetHandbrakeInput(true);

	// call the Blueprint hook for the break lights
	BrakeLights(true);
}

void AExMa_RePawn::StopHandbrake(const FInputActionValue& Value)
{
	// add the input
	ChaosVehicleMovement->SetHandbrakeInput(false);

	// call the Blueprint hook for the break lights
	BrakeLights(false);
}

void AExMa_RePawn::LookAround(const FInputActionValue& Value)
{
	// get the flat angle value for the input 
	FVector2D LookValue = Value.Get<FVector2D>();

	FRotator CurrentRotation = BackSpringArm->GetRelativeRotation();

	//TODO:
	//* XSensitivity (Add here but set & implement in settings config)
	float NewYaw = CurrentRotation.Yaw + LookValue.X * CameraSensivity;

	//TODO:
	//* YSensitivity (Add here but set & implement in settings config)
	//min & max of clamp set by DT config
	float NewPitch = FMath::Clamp(CurrentRotation.Pitch + LookValue.Y * CameraSensivity, MaxCameraPitch, MinCameraPitch);

	// add the input
	BackSpringArm->SetRelativeRotation(FRotator(NewPitch, NewYaw, 0.0f));
}

void AExMa_RePawn::ToggleCamera(const FInputActionValue& Value)
{
	// toggle the active camera flag
	bFrontCameraActive = !bFrontCameraActive;

	FrontCamera->SetActive(bFrontCameraActive);
	BackCamera->SetActive(!bFrontCameraActive);
}

void AExMa_RePawn::ToggleInventory(const FInputActionValue& Value)
{
	if (bIsPickingItems && InterractedCrates.Num() > 0)
	{
		ProcessPickupItems();
		return;
	}

	if (HUD)
		HUD->ToggleWidgetVisibility();
}

void AExMa_RePawn::ProcessPickupItems()
{
	bool bIsFullProcessComplete = true;

	UE_LOG(LogTemp, Warning, TEXT("AExMa_RePawn:: InterractedCratesAmount before transfer: %i"), InterractedCrates.Num());

	TArray<AItemActor*> ItemActors = TArray<AItemActor*>(&InterractedCrates.GetData()[0], InterractedCrates.Num());
	for (AItemActor* ItemActor : ItemActors)
	{
		if (ItemActor->TryTransferStoredItems(InventoryComponent) == false)
		{
			bIsPickingItems = false;
			bIsFullProcessComplete = false;
		}
	}

	//Remove empty & deleted crates from interacted array
	//for (int Index = 0; Index < InterractedCrates.Num(); Index++)
	//{
	//	AItemActor* ActorToRemove = InterractedCrates[Index];
	//
	//	if (ActorToRemove == NULL)
	//	{
	//		InterractedCrates.RemoveAt(Index);
	//		Index--;
	//		UE_LOG(LogTemp, Warning, TEXT("AExMa_RePawn:: EPMTYcRATE IS REMOVED FROM INTERACTION ARRAY"));
	//	}
	//}

	//If have items to transfer but player inventory is already full
	UE_LOG(LogTemp, Warning, TEXT("AExMa_RePawn:: InterractedCratesAmount after transfer: %i"), InterractedCrates.Num());

	if (bIsFullProcessComplete == false)
	{
		for (AItemActor* ItemActor : InterractedCrates)
		{
			if(ItemActor->GetStoredItemsAmount() > 0)
				ItemActor->TryCopyStoredItems(OutInventoryComponent);
		}

		if (HUD)
			HUD->ToggleWidgetVisibility();
	}
}

void AExMa_RePawn::ResetVehicle(const FInputActionValue& Value)
{
	// reset to a location slightly above our current one
	FVector ResetLocation = GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);

	// reset to our yaw. Ignore pitch and roll
	FRotator ResetRotation = GetActorRotation();
	ResetRotation.Pitch = 0.0f;
	ResetRotation.Roll = 0.0f;
	
	// teleport the actor to the reset spot and reset physics
	SetActorTransform(FTransform(ResetRotation, ResetLocation, FVector::OneVector), false, nullptr, ETeleportType::TeleportPhysics);

	GetMesh()->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	GetMesh()->SetPhysicsLinearVelocity(FVector::ZeroVector);

	UE_LOG(LogTemplateVehicle, Error, TEXT("Reset Vehicle"));
}

int AExMa_RePawn::GetHealth() const
{
	return Attributes->GetHealth();
}

int AExMa_RePawn::GetMaxHealth() const
{
	return Attributes->GetMaxHealth();
}

UExMa_VehicleAttributes* AExMa_RePawn::GetAttributes()
{
	return Attributes;
}

void AExMa_RePawn::SetupVehicleAttributes()
{
	FVehicleConfigStruct ConfigStruct;
	if (const FVehicleConfigStruct* ConfigStructRow = DataTable->FindRow<FVehicleConfigStruct>(VehicleConfigRowName, ""))
		ConfigStruct = *ConfigStructRow;

	Attributes->InitHealth(ConfigStruct.MaxHealth);
	Attributes->InitMaxHealth(ConfigStruct.MaxHealth);
	Attributes->InitArmor(ConfigStruct.Armor);
	Attributes->InitGasTankSize(ConfigStruct.GasTankSize);
	Attributes->InitTrankSize(ConfigStruct.TrankSize);
	Attributes->InitMaxTorque(ConfigStruct.MaxTorque);
	Attributes->InitMaxRPM(ConfigStruct.MaxRPM);
	Attributes->InitEngineIdleRPM(ConfigStruct.EngineIdleRPM);
	Attributes->InitEngineBrakeEffect(ConfigStruct.EngineBrakeEffect);
	Attributes->InitEngineRPMSpeedup(ConfigStruct.EngineRPMSpeedup);
	Attributes->InitEngineRPMSlowdown(ConfigStruct.EngineRPMSlowdown);
	Attributes->InitTopSpeed(ConfigStruct.TopSpeed);
	Attributes->InitEnginePower(ConfigStruct.EnginePower);
	Attributes->InitChassisHeight(ConfigStruct.ChassisHeight);
	Attributes->InitDragCoefficient(ConfigStruct.DragCoefficient);
	Attributes->InitDownforceCoefficient(ConfigStruct.DownforceCoefficient);
	Attributes->InitWeight(ConfigStruct.Weight);
	Attributes->InitBulletResistance(ConfigStruct.BulletResistance);
	Attributes->InitExplosionResistance(ConfigStruct.ExplosionResistance);
	Attributes->InitEnergyResistance(ConfigStruct.EnergyResistance);

	ApplyVehicleAttributes();
}

void AExMa_RePawn::ApplyVehicleAttributes()
{
	// Set up the engine
	// NOTE: Check the Blueprint asset for the Torque Curve
	GetChaosVehicleMovement()->EngineSetup.MaxTorque = Attributes->MaxTorque.GetCurrentValue();;
	GetChaosVehicleMovement()->EngineSetup.MaxRPM = Attributes->MaxRPM.GetCurrentValue();
	GetChaosVehicleMovement()->EngineSetup.EngineIdleRPM = Attributes->EngineIdleRPM.GetCurrentValue();
	GetChaosVehicleMovement()->EngineSetup.EngineBrakeEffect = Attributes->EngineBrakeEffect.GetCurrentValue();
	GetChaosVehicleMovement()->EngineSetup.EngineRevUpMOI = Attributes->EngineRPMSpeedup.GetCurrentValue();
	GetChaosVehicleMovement()->EngineSetup.EngineRevDownRate = Attributes->EngineRPMSlowdown.GetCurrentValue();

	// Set up the chassis
	GetChaosVehicleMovement()->ChassisHeight = Attributes->ChassisHeight.GetCurrentValue();;
	GetChaosVehicleMovement()->DragCoefficient = Attributes->DragCoefficient.GetCurrentValue();;
	GetChaosVehicleMovement()->DownforceCoefficient = Attributes->DownforceCoefficient.GetCurrentValue();
	GetChaosVehicleMovement()->CenterOfMassOverride = FVector(0.0f, 0.0f, 75.0f);
	GetChaosVehicleMovement()->bEnableCenterOfMassOverride = true;

}

//TODO: show player pickup UI hint with binded hotkey instead of straigth pickup
void AExMa_RePawn::OnCollectSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AItemActor* Chest = Cast<AItemActor>(OtherActor))
	{
		InterractedCrates.AddUnique(Chest);
		UE_LOG(LogTemp, Warning, TEXT("AExMa_RePawn:: Add interacted crate to array"));
	}
	
	if (InterractedCrates.Num() > 0)
	{
		bIsPickingItems = true;

		if (HUD)
			HUD->TogglePickupHintVisibility(true);
	}

	//if (AItemActor* Chest = Cast<AItemActor>(OtherActor))
	//{
	//	UE_LOG(LogTemp, Error, TEXT("AExMa_RePawn: Overlap with AItemActor. His amount of stored items is: %i"), Chest->GetStoredItems().Num());
	//
	//	for(UItemObject* ItemObject : Chest->GetStoredItems())
	//	{
	//		OutInventoryComponent->TryAddItem(ItemObject);
	//	}
	//	//if (PlayerPawn->GetInventoryComponent()->TryAddItem(ItemObject))
	//	//	Destroy();
	//}
}

void AExMa_RePawn::OnCollectSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (AItemActor* Chest = Cast<AItemActor>(OtherActor))
	{
		if (InterractedCrates.Contains(Chest))
		{
			Chest->ClearCopiedItemsFrom(OutInventoryComponent);
			int32 IndexToRemove = InterractedCrates.Find(Chest);
			InterractedCrates.RemoveAt(IndexToRemove);
			UE_LOG(LogTemp, Warning, TEXT("AExMa_RePawn:: Remove interacted crate to array"));
		}
	}
	
	if (InterractedCrates.Num() <= 0)
	{
		bIsPickingItems = false;

		if (HUD)
			HUD->TogglePickupHintVisibility(false);
	}
}

#undef LOCTEXT_NAMESPACE