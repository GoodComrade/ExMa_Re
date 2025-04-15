// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "ExMa_Re/Structs/TileStruct.h"
#include "ExMa_Re/Vehicles/VehicleParts/VehiclePart.h"

#include "Engine/StaticMesh.h"

#include "VehiclePartDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FWeaponSlotInfo
{
	GENERATED_BODY();

	// Ключ будет генерироваться автоматически, поэтому делаем его только для чтения в редакторе
	UPROPERTY(VisibleInstanceOnly, Category = "MyEntry")
	FString Key;

	// Вектор, редактируемый пользователем
	UPROPERTY(EditAnywhere, Category = "MyEntry")
	FTileStruct Value;
	
	// Метод для обновления ключа исходя из Value
	void UpdateKey()
	{
		// Пример: ключ формируется как "X_Y" с двумя значениями Value, можно настроить форматирование под ваши нужды
		Key = FString::Printf(TEXT("%dx%d_"), Value.X, Value.Y);
	}
};

UCLASS()
class EXMA_RE_API UVehiclePartDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UVehiclePartDataAsset(const FObjectInitializer& ObjectInitializer);

	TSubclassOf<AVehiclePart> GetVehiclePartClass() { return VehiclePartClass; }

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Health = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxHealth = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Armor = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxArmor = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Weight = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Cost = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BulletResistance = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ExplosionResistance = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float EnergyResistance = 0;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	//TArray<FTileStruct> WeaponSlots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FWeaponSlotInfo> WeaponSlots;

	TMap<FString, FTileStruct> WeaponSlotsMap;

#if WITH_EDITOR
	// Функция, вызываемая при изменении свойства в редакторе
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
	
#endif

	virtual void PostLoad() override;
	
protected:
	//TODO: implement AVehiclePart class & set their static version here 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AVehiclePart> VehiclePartClass;


	//TODO: Переделать тут массив слотов под оружие в виде TMap
	// где 'ключ - Искомый префикс в названии меша', а 'значение - FTileStruct'
	// Эта карта затем будет передана в WeaponComponent вместе со всеми собранными с игрока сокетами
	// Префикс должен задаваться в формате "X x Y_" где X Y это значения из FTileStruct

};
