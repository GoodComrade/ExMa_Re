// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemActor.h"
#include "ExMa_Re/Weapons/ExMa_WeaponAttributes.h"
#include "ExMa_Re/DataAssets/WeaponDataAsset.h"
#include "Animation/AnimBlueprint.h"
#include "Animation/AnimInstance.h"
#include "WeaponActor.generated.h"

class UAbilitySystemComponent;
class USkeletalMesh;

UCLASS(Blueprintable, BlueprintType)
class EXMA_RE_API AWeaponActor : public AItemActor
{
	GENERATED_BODY()
	
public:
	AWeaponActor();

	virtual void Tick(float Delta) override;

	//UFUNCTION(BlueprintCallable)
	//void SetWeaponAttributes(FWeaponConfigStruct WeaponConfig);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = Abilities)
	UAbilitySystemComponent* AbilitySystem;

	UPROPERTY(BlueprintReadOnly, Category = Abilities)
	UExMa_WeaponAttributes* Attributes;

public:
	UFUNCTION()
	void SetWeaponOwner(AActor* OwnerToSet);

	UFUNCTION()
	void SetMesh(USkeletalMesh* MeshToSet);

	UFUNCTION()
	void SetMeshAnimInstance(UAnimBlueprint* AnimToSet);

	UFUNCTION()
	void SetWeaponData(UWeaponDataAsset* DataToSet);

public:
	UFUNCTION(BlueprintCallable)
	AActor* GetWeaponOwner() const { return WeaponOwner; };

	UFUNCTION(BlueprintCallable)
	class USkeletalMeshComponent* GetMesh() const { return Mesh; }

	UFUNCTION(BlueprintCallable)
	UExMa_WeaponAttributes* GetWeaponAttributes() const { return Attributes; };

	UFUNCTION(BlueprintCallable)
	UWeaponDataAsset* GetWeaponData() const { return WeaponData; };


private:

	UPROPERTY(Category = Weapon, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> Mesh;

	UPROPERTY(Category = Weapon, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWeaponDataAsset* WeaponData;

	UPROPERTY()
	AActor* WeaponOwner = nullptr;
};
