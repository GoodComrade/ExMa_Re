// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExMa_RePawn.h"
#include "ExMa_Re/Wheels/ExMa_ReWheelFront.h"
#include "ExMa_Re/Wheels/ExMa_ReWheelRear.h"

#include "ExMa_Re/Components/InventoryComponent.h"
#include "ExMa_Re/Components/StructuralComponent.h"
#include "ExMa_Re/Components/WeaponComponent.h"

#include "ExMa_Re/UI/ExMaHUD.h"
#include "ExMa_Re/Items/ItemActor.h"
#include "ExMa_Re/Items/ItemObject.h"
#include "ExMa_Re/Game/ExMa_GameState.h"
#include "ExMa_Re/Items/ChestActor.h"
#include "ExMa_Re/Enums/VehicleType.h"

#include "ExMa_Re/DataAssets/Vehicles/VehicleParts/VehiclePartDataAsset.h"
#include "ExMa_Re/DataAssets/Vehicles/VehicleParts/Car/CarBodyDataAsset.h"
#include "ExMa_Re/DataAssets/Vehicles/VehicleParts/Truck/TruckCabinDataAsset.h"
#include "ExMa_Re/DataAssets/Vehicles/VehicleParts/Truck/TruckBodyDataAsset.h"

#include "ExMa_Re/Game/ExMa_GameInstance.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ExMa_VehicleAttributes.h"
#include "ChaosWheeledVehicleMovementComponent.h"

#include "Kismet/GameplayStatics.h"


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

	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AblitySystem"));

	Attributes = CreateDefaultSubobject<UExMa_VehicleAttributes>(TEXT("AttributeSet"));
	AbilitySystem->AddSpawnedAttribute(Attributes);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	OutInventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("OutInventoryComponent"));

	StructuralComponent = CreateDefaultSubobject<UStructuralComponent>(TEXT("StructuralComponent"));

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));

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

AExMa_GameState* AExMa_RePawn::GetGameState()
{
	UWorld* World = GetWorld();

	if (World == nullptr)
		return nullptr;

	AExMa_GameState* GameState = World->GetGameState<AExMa_GameState>();

	if (GameState == nullptr)
		return nullptr;

	return GameState;
}

FVector AExMa_RePawn::GetCameraLookAtDirection() const
{
	if(!BackCamera)
		return FVector::ZeroVector;

	// Точка начала взгляда (камера)
	FVector Start = BackCamera->GetComponentLocation();

	// Направление взгляда
	FVector Forward = BackCamera->GetForwardVector();

	return Start + (Forward * 10000.0f); // Точка "в бесконечности"
}

void AExMa_RePawn::BeginPlay()
{
	Super::BeginPlay();

	UExMa_GameInstance* GameInstance = Cast<UExMa_GameInstance>(GetGameInstance());

	if (GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_RePawn:: GameInstance is NULLPTR!"));
		return;
	}

	InventoryComponent->TileSize = GameInstance->TileSize;

	HUD = Cast<AExMaHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (HUD)
	{
		HUD->InitInteractionWidget(GetInventoryComponent(), GetOutInventoryComponent(), GetWeaponComponent());
		HUD->InitPickupHintWidget();
	}

	SetupBaseVehicleAttributes();
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
	UWorld* World = GetWorld();

	if (World == nullptr)
		return;

	if (bIsPickingItems && InterractedCrates.Num() > 0)
	{
		ProcessPickupItems();
		return;
	}

	if (UGameplayStatics::IsGamePaused(World) && OutInventoryComponent->GetAllItems().Num() > 0)
	{
		ProcessSpawnCrate();
	}

	if (HUD)
		HUD->ToggleWidgetVisibility(!UGameplayStatics::IsGamePaused(World));
}

void AExMa_RePawn::AddItemObjectToInventory(UItemObject* ItemToAdd)
{
	if (!ItemToAdd)
		return;

	if (InventoryComponent->TryAddItem(ItemToAdd))
		return;

	if (OutInventoryComponent->TryAddItem(ItemToAdd))
		return;

	UE_LOG(LogTemp, Warning, TEXT("AExMa_RePawn::AddItemObjectToInventory: Fail to return item to inventory"));
}

bool AExMa_RePawn::IsDead()
{
	return false;
}

void AExMa_RePawn::ProcessPickupItems()
{
	UE_LOG(LogTemp, Warning, TEXT("AExMa_RePawn:: InterractedCratesAmount before transfer: %i"), InterractedCrates.Num());

	TArray<AChestActor*> ChestActors = TArray<AChestActor*>(&InterractedCrates.GetData()[0], InterractedCrates.Num());
	for (AChestActor* Chest : ChestActors)
	{
		if (Chest->TryTransferStoredItems(InventoryComponent) == false)
		{
			ProcessItemsOverflow(ChestActors);
			UE_LOG(LogTemp, Warning, TEXT("AExMa_RePawn:: NO FREE SPACE IN INVENTORY: %i"), InterractedCrates.Num());
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("AExMa_RePawn:: InterractedCratesAmount after transfer: %i"), InterractedCrates.Num());
}

void AExMa_RePawn::ProcessItemsOverflow(TArray<AChestActor*> ChestActorsToProcess)
{
	bIsPickingItems = false;

	//If have items to transfer but player inventory is already full.
	//Transfer unplaced items into out inventory.
	for (AChestActor* OutChest : ChestActorsToProcess)
	{
		if (OutChest->TryTransferStoredItems(OutInventoryComponent) == false)
		{
			UE_LOG(LogTemp, Error, TEXT("AExMa_RePawn:: NO FREE SPACE IN OUT INVENTORY: %i"), InterractedCrates.Num());
			return;
		}
	}

	UWorld* World = GetWorld();

	if (World == nullptr)
		return;

	if (HUD)
		HUD->ToggleWidgetVisibility(!UGameplayStatics::IsGamePaused(World));
}

void AExMa_RePawn::ProcessSpawnCrate()
{
	if (GetGameState() == nullptr)
		return;

	GetGameState()->SpawnCrateActorFromPawn(ChestClass, GetOutInventoryComponent(), this, true);
}

void AExMa_RePawn::ProcessTogglePickupState(bool NewState)
{
	if (!HUD)
	{
		UE_LOG(LogTemplateVehicle, Error, TEXT("AExMa_RePawn::ProcessTogglePickupState: HUD is nullptr."));
		return;
	}

	bIsPickingItems = NewState;

	if (HUD)
		HUD->TogglePickupHintVisibility(NewState);
}

void AExMa_RePawn::SetVehicleData(UVehicleDataAsset* DataToSet)
{
	VehicleData = DataToSet;
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

void AExMa_RePawn::SetupBaseVehicleAttributes()
{
	if (VehicleData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_RePawn:: VehicleData is NULLPTR!"));
		return;
	}

	//TODO: Переделать так, что бы атрибуты сетались в StructuralComponent
	Attributes->InitHealth(VehicleData->Health);
	Attributes->InitMaxHealth(VehicleData->MaxHealth);
	Attributes->InitArmor(VehicleData->Armor);
	Attributes->InitMaxArmor(VehicleData->MaxArmor);

	Attributes->InitGasTankSize(0);
	Attributes->InitMaxTorque(0);
	Attributes->InitMaxRPM(0);
	Attributes->InitEngineIdleRPM(0);
	Attributes->InitEngineBrakeEffect(0);
	Attributes->InitEngineRPMSpeedup(0);
	Attributes->InitEngineRPMSlowdown(0);
	Attributes->InitTopSpeed(0);
	Attributes->InitEnginePower(0);
	Attributes->InitChassisHeight(0);
	Attributes->InitDragCoefficient(0);
	Attributes->InitDownforceCoefficient(0);

	Attributes->InitWeight(VehicleData->Weight);
	Attributes->InitMaxWeight(VehicleData->MaxWeight);
	Attributes->InitBulletResistance(VehicleData->BulletResistance);
	Attributes->InitExplosionResistance(VehicleData->ExplosionResistance);
	Attributes->InitEnergyResistance(VehicleData->EnergyResistance);

	ApplyVehicleAttributes();
}


void AExMa_RePawn::SetVehicleCabin(AVehiclePart* CabinToSet)
{
	//TODO: implement here weapon slots init
	UTruckCabinDataAsset* TruckCabinData = Cast<UTruckCabinDataAsset>(CabinToSet->GetVehiclePartData());

	if (!TruckCabinData)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_RePawn::SetVehicleCabin: TruckCabinData IS NULLPTR!"));
		return;
	}

	UStaticMeshComponent* StaticMeshComponent = CabinToSet->GetVehicleStaticMeshComponent();
	if (!StaticMeshComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_RePawn::SetVehicleCabin: VehiclePart StaticMeshComponent IS NULLPTR!"));
		return;
	}

	StructuralComponent->SetVehicleCabin(CabinToSet);

	WeaponComponent->AddWeaponSlots(TruckCabinData->WeaponSlots, StaticMeshComponent);

	int32 NewHealth = Attributes->GetHealth() + TruckCabinData->Health;
	int32 NewMaxHealth = Attributes->GetMaxHealth() + TruckCabinData->MaxHealth;
	int32 NewArmor = Attributes->GetArmor() + TruckCabinData->Armor;
	int32 NewMaxArmor = Attributes->GetMaxArmor() + TruckCabinData->MaxArmor;

	Attributes->SetHealth(NewHealth);
	Attributes->SetMaxHealth(NewMaxHealth);
	Attributes->SetArmor(NewArmor);
	Attributes->SetMaxArmor(NewMaxArmor);

	Attributes->SetGasTankSize(TruckCabinData->GasTankSize);
	Attributes->SetMaxTorque(TruckCabinData->MaxTorque);
	Attributes->SetMaxRPM(TruckCabinData->MaxRPM);
	Attributes->SetEngineIdleRPM(TruckCabinData->EngineIdleRPM);
	Attributes->SetEngineBrakeEffect(TruckCabinData->EngineBrakeEffect);
	Attributes->SetEngineRPMSpeedup(TruckCabinData->EngineRPMSpeedup);
	Attributes->SetEngineRPMSlowdown(TruckCabinData->EngineRPMSlowdown);
	Attributes->SetTopSpeed(TruckCabinData->TopSpeed);
	Attributes->SetEnginePower(TruckCabinData->EnginePower);
	Attributes->SetChassisHeight(TruckCabinData->ChassisHeight);
	Attributes->SetDragCoefficient(TruckCabinData->DragCoefficient);
	Attributes->SetDownforceCoefficient(TruckCabinData->DownforceCoefficient);

	ApplyVehicleAttributes();
}

void AExMa_RePawn::SetVehicleBody(AVehiclePart* BodyToSet)
{
	//TODO: implement here weapon slots init
	UVehiclePartDataAsset* VehiclePartData = BodyToSet->GetVehiclePartData();

	if (!VehiclePartData)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_RePawn::SetVehicleCabin: VehiclePartData IS NULLPTR!"));
		return;
	}

	UStaticMeshComponent* StaticMeshComponent = BodyToSet->GetVehicleStaticMeshComponent();
	if (!StaticMeshComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_RePawn::SetVehicleCabin: VehiclePart StaticMeshComponent IS NULLPTR!"));
		return;
	}

	StructuralComponent->SetVehicleBody(BodyToSet);
	WeaponComponent->AddWeaponSlots(VehiclePartData->WeaponSlots, StaticMeshComponent);

	int32 NewHealth = Attributes->GetHealth() + VehiclePartData->Health;
	int32 NewMaxHealth = Attributes->GetMaxHealth() + VehiclePartData->MaxHealth;
	int32 NewArmor = Attributes->GetArmor() + VehiclePartData->Armor;
	int32 NewMaxArmor = Attributes->GetMaxArmor() + VehiclePartData->MaxArmor;

	Attributes->SetHealth(NewHealth);
	Attributes->SetMaxHealth(NewMaxHealth);
	Attributes->SetArmor(NewArmor);
	Attributes->SetMaxArmor(NewMaxArmor);

	if (VehicleData->VehicleType == EVehicleType::CAR)
	{
		UCarBodyDataAsset* CarBodyData = Cast<UCarBodyDataAsset>(VehiclePartData);

		if (CarBodyData == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AExMa_RePawn:: CarBodyData IS NULLPTR!"));
			return;
		}

		InventoryComponent->SetInventorySize(CarBodyData->TrunkSize.X, CarBodyData->TrunkSize.Y);

		Attributes->SetGasTankSize(CarBodyData->GasTankSize);
		Attributes->SetMaxTorque(CarBodyData->MaxTorque);
		Attributes->SetMaxRPM(CarBodyData->MaxRPM);
		Attributes->SetEngineIdleRPM(CarBodyData->EngineIdleRPM);
		Attributes->SetEngineBrakeEffect(CarBodyData->EngineBrakeEffect);
		Attributes->SetEngineRPMSpeedup(CarBodyData->EngineRPMSpeedup);
		Attributes->SetEngineRPMSlowdown(CarBodyData->EngineRPMSlowdown);
		Attributes->SetTopSpeed(CarBodyData->TopSpeed);
		Attributes->SetEnginePower(CarBodyData->EnginePower);
		Attributes->SetChassisHeight(CarBodyData->ChassisHeight);
		Attributes->SetDragCoefficient(CarBodyData->DragCoefficient);
		Attributes->SetDownforceCoefficient(CarBodyData->DownforceCoefficient);

		ApplyVehicleAttributes();

		return;
	}

	UTruckBodyDataAsset* TruckBodyData = Cast<UTruckBodyDataAsset>(VehiclePartData);

	if (TruckBodyData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_RePawn:: TruckBodyData IS NULLPTR!"));
		return;
	}

	InventoryComponent->SetInventorySize(TruckBodyData->TrunkSize.X, TruckBodyData->TrunkSize.Y);

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

UAbilitySystemComponent* AExMa_RePawn::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}

//TODO: show player pickup UI hint with binded hotkey instead of straigth pickup
void AExMa_RePawn::OnCollectSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AChestActor* Chest = Cast<AChestActor>(OtherActor))
	{
		InterractedCrates.AddUnique(Chest);
		UE_LOG(LogTemp, Warning, TEXT("AExMa_RePawn:: Add interacted crate to array"));
	}
	
	ProcessTogglePickupState(InterractedCrates.Num() > 0 && !bIsPickingItems);

	//if (InterractedCrates.Num() > 0)
	//{
	//	bIsPickingItems = true;
	//
	//	if (HUD)
	//		HUD->TogglePickupHintVisibility(true);
	//}

}

void AExMa_RePawn::OnCollectSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (AChestActor* Chest = Cast<AChestActor>(OtherActor))
	{
		if (InterractedCrates.Contains(Chest))
		{
			int32 IndexToRemove = InterractedCrates.Find(Chest);
			InterractedCrates.RemoveAt(IndexToRemove);
			UE_LOG(LogTemp, Warning, TEXT("AExMa_RePawn:: Remove interacted crate to array"));
		}
	}
	
	ProcessTogglePickupState(InterractedCrates.Num() > 0 && bIsPickingItems);

	//if (InterractedCrates.Num() <= 0)
	//{
	//	bIsPickingItems = false;
	//
	//	if (HUD)
	//		HUD->TogglePickupHintVisibility(false);
	//}
}

#undef LOCTEXT_NAMESPACE