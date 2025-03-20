// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemObject.h"
#include "ExMa_Re/Enums/WeaponType.h"
#include "ExMa_Re/Enums/WeaponDamageType.h"
#include "ExMa_Re/ConfigStruct/WeaponConfigStruct.h"
//#include "ExMa_Re/Weapons/ExMa_WeaponAttributes.h"
#include "WeaponItemObject.generated.h"

class UExMa_WeaponAttributes;

UCLASS()
class EXMA_RE_API UWeaponItemObject : public UItemObject
{
	GENERATED_BODY()

	
public:
	UWeaponItemObject();

	

	UFUNCTION(BlueprintCallable)
	void SetWeaponType(EWeaponType NewWeaponType);

	UFUNCTION(BlueprintCallable)
	void SetWeaponDamageType(EWeaponDamageType NewDamageType);

	virtual void SetItemInfo() override;

	UFUNCTION(BlueprintCallable)
	EWeaponType GetWeaponType() const { return WeaponType; };

	UFUNCTION(BlueprintCallable)
	EWeaponDamageType GetWeaponDamageType() const { return DamageType; };

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	EWeaponType WeaponType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	EWeaponDamageType DamageType;

private:
	double CalculateEffectiveRPM(double ShootDelay, int MagazineSize, double ReloadTime);
};
