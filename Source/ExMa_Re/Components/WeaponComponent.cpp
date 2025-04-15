// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponComponent.h"
#include "ExMa_Re/Weapons/WeaponSlot.h"
#include "ExMa_Re/Structs/TileStruct.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponComponent::AddWeaponSlots(TArray<FTileStruct> SlotsDimentions)
{
	if (SlotsDimentions.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("UWeaponComponent:: SlotsDimentionsArray IS EMPTY!"));
		return;
	}

	for (FTileStruct Dimentions : SlotsDimentions)
	{
		UWeaponSlot* WeaponSlot = NewObject<UWeaponSlot>(UWeaponSlot::StaticClass());
		WeaponSlot->SetSlotDimensions(Dimentions);

		WeaponSlots.AddUnique(WeaponSlot);
	}
}

UWeaponSlot* UWeaponComponent::GetSlotByIndex(int SlotIndex)
{
	return WeaponSlots[SlotIndex];
}

