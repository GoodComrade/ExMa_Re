// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemActor.h"
#include "ExMa_Re/Weapons/ExMa_WeaponAttributes.h"
#include "WeaponActor.generated.h"

class UAbilitySystemComponent;

UCLASS()
class EXMA_RE_API AWeaponActor : public AItemActor
{
	GENERATED_BODY()
	
public:
	AWeaponActor();

	virtual void Tick(float Delta) override;

	UFUNCTION()
	UExMa_WeaponAttributes* GetAttributes() const { return Attributes; };

	//UFUNCTION(BlueprintCallable)
	//void SetWeaponAttributes(FWeaponConfigStruct WeaponConfig);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = Abilities)
	UAbilitySystemComponent* AbilitySystem;

	UPROPERTY(BlueprintReadOnly, Category = Abilities)
	UExMa_WeaponAttributes* Attributes;
};
