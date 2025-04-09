// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StructuralComponent.h"

// Sets default values for this component's properties
UStructuralComponent::UStructuralComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	VehicleCabin = nullptr;
	VehicleBody = nullptr;
}


// Called when the game starts
void UStructuralComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void UStructuralComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UStructuralComponent::SetVehicleCabin(AVehiclePart* CabinToSet)
{
	DestroyCabin();

	VehicleCabin = CabinToSet;
	VehicleCabin->AttachToComponent(ChassisMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("CabinSocket"));
	VehicleCabin->SetRootComponent(ChassisMesh);
}

void UStructuralComponent::SetVehicleBody(AVehiclePart* BodyToSet)
{
	DestroyBody();

	VehicleBody = BodyToSet;
	VehicleBody->AttachToComponent(ChassisMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("BodySocket"));
	VehicleBody->SetRootComponent(ChassisMesh);
}

void UStructuralComponent::DestroyCabin()
{
	if (VehicleCabin != nullptr)
		VehicleCabin->Destroy();
}

void UStructuralComponent::DestroyBody()
{
	if (VehicleBody != nullptr)
		VehicleBody->Destroy();
}

