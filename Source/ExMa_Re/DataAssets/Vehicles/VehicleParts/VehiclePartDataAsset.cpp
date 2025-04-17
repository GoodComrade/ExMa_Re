// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Vehicles/VehicleParts/VehiclePartDataAsset.h"
#include "ExMa_Re/Vehicles/VehicleParts/VehiclePart.h"
#include "ExMa_Re/Structs/WeaponSlotInfo.h"


UVehiclePartDataAsset::UVehiclePartDataAsset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//VehiclePartClass = AVehiclePart::StaticClass();
	//VehiclePartMesh = nullptr;
}

#if WITH_EDITOR
void UVehiclePartDataAsset::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	// ���� ���������� �������� � �����-���� �������� �������:
	FName ChangedPropertyName = NAME_None;
	// �������� ��������� ���� �������
	if (PropertyChangedEvent.PropertyChain.GetTail() != nullptr)
	{
		// �������� ��������� �� FProperty, ��������� � ���� �����
		FProperty* LastProperty = PropertyChangedEvent.PropertyChain.GetTail()->GetValue();
		if (LastProperty)
		{
			ChangedPropertyName = LastProperty->GetFName();
		}
	}

	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(FWeaponSlotInfo, Value))
	{
		// ��������� ���� ��� ���� ��������� (��� ��� ����������, ���� ������� �������� ������)
		for (FWeaponSlotInfo& WeaponSlot : WeaponSlots)
		{
			WeaponSlot.UpdateKey();
		}
	}
}
#endif

