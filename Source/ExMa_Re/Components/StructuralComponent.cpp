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
	VehicleCabin = CabinToSet;
}

void UStructuralComponent::ChangeVehicleCabin(AVehiclePart* NewCabin)
{
	if (VehicleCabin == nullptr)
		return;

	VehicleCabin->Destroy();

	VehicleCabin = NewCabin;
}

void UStructuralComponent::SetVehicleBody(AVehiclePart* BodyToSet)
{
	VehicleBody = BodyToSet;
}

void UStructuralComponent::ChangeVehicleBody(AVehiclePart* NewBody)
{
	if (VehicleBody == nullptr)
		return;

	VehicleBody->Destroy();

	VehicleBody = NewBody;
}

