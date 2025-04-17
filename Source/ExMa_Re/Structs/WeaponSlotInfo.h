#pragma once

#include "ExMa_Re/Structs/TileStruct.h"
#include "WeaponSlotInfo.generated.h"

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