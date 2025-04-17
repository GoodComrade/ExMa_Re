// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponComponent.h"
#include "ExMa_Re/Weapons/WeaponSlot.h"
#include "ExMa_Re/Structs/TileStruct.h"
#include "Engine/StaticMeshSocket.h"
#include "Components/StaticMeshComponent.h"
#include "ExMa_Re/Structs/WeaponSlotInfo.h"

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

void UWeaponComponent::AddWeaponSlots(TArray<FWeaponSlotInfo> SlotsArray, UStaticMeshComponent* TargetMesh)
{
	if (SlotsArray.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("UWeaponComponent:: SlotsArray IS EMPTY!"));
		return;
	}

	//TArray<FName> TempSlotsNames = TArray<FName>(&SlotsNames.GetData()[0], SlotsNames.Num());

	for (FWeaponSlotInfo& SlotInfo : SlotsArray)
	{
		UWeaponSlot* WeaponSlot = NewObject<UWeaponSlot>(UWeaponSlot::StaticClass());

		FName SlotName = GetSocketNameWithPrefix(TargetMesh, SlotInfo.Key);

		WeaponSlot->SetSlotSocketName(SlotName);
		WeaponSlot->SetSlotDimensions(SlotInfo.Value);

		WeaponSlots.AddUnique(WeaponSlot);

		UE_LOG(LogTemp, Warning, TEXT("UWeaponComponent:: WeaponSlot IS CREATED!"));
		OnWeaponSlotCreated.Broadcast(WeaponSlot);
	}
}

UWeaponSlot* UWeaponComponent::GetSlotByIndex(int SlotIndex)
{
	return WeaponSlots[SlotIndex];
}

FName UWeaponComponent::GetSocketNameWithPrefix(UStaticMeshComponent* StaticMeshComponent, const FString& Prefix)
{
	FName SocketName;

	if (!StaticMeshComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("AExMa_RePawn::GetSocketNamesWithPrefix: StaticMeshComponent == nullptr"));
		return SocketName;
	}

	UStaticMesh* Mesh = StaticMeshComponent->GetStaticMesh();
	if (!Mesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("AExMa_RePawn::GetSocketNamesWithPrefix: Mesh == nullptr"));
		return SocketName;
	}

	// Итерируемся по массиву сокетов в статической сетке
	for (const UStaticMeshSocket* Socket : Mesh->Sockets)
	{
		if (Socket)
		{
			// Преобразуем FName сокета в строку для проверки префикса
			FString SocketNameString = Socket->SocketName.ToString();
			if (SocketNameString.StartsWith(Prefix))
			{
				SocketName = Socket->SocketName;
			}
		}
	}

	return SocketName;

};