// Copyright Epic Games, Inc. All Rights Reserved.


#include "ExMa_ReOffroadCar.h"
#include "ExMa_Re/Vehicles/VehicleParts/DestroyedPart.h"
#include "ExMa_Re/Wheels/Offroad/ExMa_ReOffroadWheelFront.h"
#include "ExMa_Re/Wheels/Offroad/ExMa_ReOffroadWheelRear.h"
#include "ExMa_Re/Components/StructuralComponent.h"
#include "ExMa_Re/Components/WeaponComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AExMa_ReOffroadCar::AExMa_ReOffroadCar()
{
	// construct the mesh components
	Chassis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chassis"));
	Chassis->SetupAttachment(GetMesh());

	// NOTE: tire sockets are set from the Blueprint class
	TireFrontLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tire Front Left"));
	TireFrontLeft->SetupAttachment(GetMesh(), FName("VisWheel_FL"));
	TireFrontLeft->SetCollisionProfileName(FName("NoCollision"));

	TireFrontRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tire Front Right"));
	TireFrontRight->SetupAttachment(GetMesh(), FName("VisWheel_FR"));
	TireFrontRight->SetCollisionProfileName(FName("NoCollision"));
	TireFrontRight->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));

	TireRearLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tire Rear Left"));
	TireRearLeft->SetupAttachment(GetMesh(), FName("VisWheel_BL"));
	TireRearLeft->SetCollisionProfileName(FName("NoCollision"));

	TireRearRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tire Rear Right"));
	TireRearRight->SetupAttachment(GetMesh(), FName("VisWheel_BR"));
	TireRearRight->SetCollisionProfileName(FName("NoCollision"));
	TireRearRight->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));

	// adjust the cameras
	GetFrontSpringArm()->SetRelativeLocation(FVector(-5.0f, -30.0f, 135.0f));
	GetBackSpringArm()->SetRelativeLocation(FVector(0.0f, 0.0f, 75.0f));

	// Note: for faster iteration times, the vehicle setup can be tweaked in the Blueprint instead

	// Set up the chassis
	//GetChaosVehicleMovement()->ChassisHeight = 160.0f;
	//GetChaosVehicleMovement()->DragCoefficient = 0.1f;
	//GetChaosVehicleMovement()->DownforceCoefficient = 0.1f;
	//GetChaosVehicleMovement()->CenterOfMassOverride = FVector(0.0f, 0.0f, 75.0f);
	//GetChaosVehicleMovement()->bEnableCenterOfMassOverride = true;

	// Set up the wheels
	GetChaosVehicleMovement()->bLegacyWheelFrictionPosition = true;
	GetChaosVehicleMovement()->WheelSetups.SetNum(4);

	GetChaosVehicleMovement()->WheelSetups[0].WheelClass = UExMa_ReOffroadWheelFront::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[0].BoneName = FName("PhysWheel_FL");
	GetChaosVehicleMovement()->WheelSetups[0].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetChaosVehicleMovement()->WheelSetups[1].WheelClass = UExMa_ReOffroadWheelFront::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[1].BoneName = FName("PhysWheel_FR");
	GetChaosVehicleMovement()->WheelSetups[1].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetChaosVehicleMovement()->WheelSetups[2].WheelClass = UExMa_ReOffroadWheelRear::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[2].BoneName = FName("PhysWheel_BL");
	GetChaosVehicleMovement()->WheelSetups[2].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetChaosVehicleMovement()->WheelSetups[3].WheelClass = UExMa_ReOffroadWheelRear::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[3].BoneName = FName("PhysWheel_BR");
	GetChaosVehicleMovement()->WheelSetups[3].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	// Set up the engine
	// NOTE: Check the Blueprint asset for the Torque Curve
	//GetChaosVehicleMovement()->EngineSetup.MaxTorque = 600.0f;
	//GetChaosVehicleMovement()->EngineSetup.MaxRPM = 5000.0f;
	//GetChaosVehicleMovement()->EngineSetup.EngineIdleRPM = 1200.0f;
	//GetChaosVehicleMovement()->EngineSetup.EngineBrakeEffect = 0.05f;
	//GetChaosVehicleMovement()->EngineSetup.EngineRevUpMOI = 5.0f;
	//GetChaosVehicleMovement()->EngineSetup.EngineRevDownRate = 600.0f;

	// Set up the differential
	GetChaosVehicleMovement()->DifferentialSetup.DifferentialType = EVehicleDifferential::AllWheelDrive;
	GetChaosVehicleMovement()->DifferentialSetup.FrontRearSplit = 0.5f;

	// Set up the steering
	// NOTE: Check the Blueprint asset for the Steering Curve
	GetChaosVehicleMovement()->SteeringSetup.SteeringType = ESteeringType::AngleRatio;
	GetChaosVehicleMovement()->SteeringSetup.AngleRatio = 0.7f;

	StructuralComponent->ChassisMesh = Chassis;
}

void AExMa_ReOffroadCar::BeginPlay()
{
	Super::BeginPlay();
}

void AExMa_ReOffroadCar::OnDeath()
{
	ProcessDetachWheels();

	WeaponComponent->ProcessDetachWeaponsOnDeath(WeaponDeathColorTexture);

	if(StructuralComponent->GetCabin() == nullptr)
		StructuralComponent->ProcessDetachComponentsOnDeath(CarDeathColorTexture);
	else
		StructuralComponent->ProcessDetachComponentsOnDeath(TruckDeathColorTexture);

	Super::OnDeath();
}

void AExMa_ReOffroadCar::ProcessDetachWheels()
{
	FTransform TireFrontLeftWorldTransform = TireFrontLeft->GetComponentTransform();
	FTransform TireFrontRightWorldTransform = TireFrontRight->GetComponentTransform();
	FTransform TireRearLeftWorldTransform = TireRearLeft->GetComponentTransform();
	FTransform TireRearRightWorldTransform = TireRearRight->GetComponentTransform();

	ADestroyedPart* TireFrontLeftDestroyed = GetWorld()->SpawnActor<ADestroyedPart>(ADestroyedPart::StaticClass(), TireFrontLeftWorldTransform);
	if (TireFrontLeftDestroyed)
		TireFrontLeftDestroyed->Init(TireFrontLeft->GetStaticMesh(), GetActorLocation(), TruckDeathColorTexture);

	//TireFrontLeft->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	//TireFrontLeft->SetCollisionProfileName(FName("BlockAll"));
	//TireFrontLeft->SetSimulatePhysics(true);
	//FVector TireFrontLeftImpulseDirection = (TireFrontLeft->GetComponentLocation() - GetActorLocation()).GetSafeNormal();
	//TireFrontLeft->AddImpulse(TireFrontLeftImpulseDirection * 500.0f, NAME_None, true);

	ADestroyedPart* TireFrontRightDestroyed = GetWorld()->SpawnActor<ADestroyedPart>(ADestroyedPart::StaticClass(), TireFrontRightWorldTransform);
	if (TireFrontRightDestroyed)
		TireFrontRightDestroyed->Init(TireFrontRight->GetStaticMesh(), GetActorLocation(), TruckDeathColorTexture);

	//TireFrontRight->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	//TireFrontRight->SetCollisionProfileName(FName("BlockAll"));
	//TireFrontRight->SetSimulatePhysics(true);
	//FVector TireFrontRightImpulseDirection = (TireFrontRight->GetComponentLocation() - GetActorLocation()).GetSafeNormal();
	//TireFrontRight->AddImpulse(TireFrontRightImpulseDirection * 500.0f, NAME_None, true);

	ADestroyedPart* TireRearLeftDestroyed = GetWorld()->SpawnActor<ADestroyedPart>(ADestroyedPart::StaticClass(), TireRearLeftWorldTransform);
	if (TireRearLeftDestroyed)
		TireRearLeftDestroyed->Init(TireRearLeft->GetStaticMesh(), GetActorLocation(), TruckDeathColorTexture);

	//TireRearLeft->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	//TireRearLeft->SetCollisionProfileName(FName("BlockAll"));
	//TireRearLeft->SetSimulatePhysics(true);
	//FVector TireRearLeftImpulseDirection = (TireRearLeft->GetComponentLocation() - GetActorLocation()).GetSafeNormal();
	//TireRearLeft->AddImpulse(TireRearLeftImpulseDirection * 500.0f, NAME_None, true);

	ADestroyedPart* TireRearRightDestroyed = GetWorld()->SpawnActor<ADestroyedPart>(ADestroyedPart::StaticClass(), TireRearRightWorldTransform);
	if (TireRearRightDestroyed)
		TireRearRightDestroyed->Init(TireRearRight->GetStaticMesh(), GetActorLocation(), TruckDeathColorTexture);

	//TireRearRight->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	//TireRearRight->SetCollisionProfileName(FName("BlockAll"));
	//TireRearRight->SetSimulatePhysics(true);
	//FVector TireRearRightImpulseDirection = (TireRearRight->GetComponentLocation() - GetActorLocation()).GetSafeNormal();
	//TireRearRight->AddImpulse(TireRearRightImpulseDirection * 500.0f, NAME_None, true);
}
