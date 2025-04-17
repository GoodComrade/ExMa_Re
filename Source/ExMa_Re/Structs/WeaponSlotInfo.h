#pragma once

#include "ExMa_Re/Structs/TileStruct.h"
#include "WeaponSlotInfo.generated.h"

USTRUCT(BlueprintType)
struct FWeaponSlotInfo
{
	GENERATED_BODY();

	// ���� ����� �������������� �������������, ������� ������ ��� ������ ��� ������ � ���������
	UPROPERTY(VisibleInstanceOnly, Category = "MyEntry")
	FString Key;

	// ������, ������������� �������������
	UPROPERTY(EditAnywhere, Category = "MyEntry")
	FTileStruct Value;

	// ����� ��� ���������� ����� ������ �� Value
	void UpdateKey()
	{
		// ������: ���� ����������� ��� "X_Y" � ����� ���������� Value, ����� ��������� �������������� ��� ���� �����
		Key = FString::Printf(TEXT("%dx%d_"), Value.X, Value.Y);
	}
};