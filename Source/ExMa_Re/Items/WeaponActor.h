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
class UAbilityContainer;
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

#pragma region WeaponActor

public:
	UFUNCTION()
	void SetWeaponData(UWeaponDataAsset* DataToSet);

	UFUNCTION()
	void SetWeaponOwner(AActor* OwnerToSet);

	UFUNCTION()
	void SetWeaponParamsFromData();

private:
	void SetMesh();

	void SetMeshAnimInstance();

	void SetWeaponAbilities();

	void SetAttributes();

	void SetAnimMotages();

#pragma endregion PropertySetters

#pragma region WeaponActor
public:
	UFUNCTION()
	void RemoveWeaponParams();

private:
	UFUNCTION()
	void RemoveWeaponOwner();

	UFUNCTION()
	void RemoveMesh();

	UFUNCTION()
	void RemovetMeshAnimInstance();

	UFUNCTION()
	void RemoveWeaponData();

	UFUNCTION()
	void RemoveAttributes();

#pragma endregion PropertyRemovers

public:
	UFUNCTION(BlueprintCallable)
	bool CastAttack();

	UFUNCTION(BlueprintCallable)
	void CastReload() const;

public:
	void DisableAbilities();
	void EnableAbilities();

public:
	UFUNCTION(BlueprintCallable)
	AActor* GetWeaponOwner() const { return WeaponOwner; };

	UFUNCTION(BlueprintCallable)
	class USkeletalMeshComponent* GetMesh() const { return Mesh; }

	UFUNCTION(BlueprintCallable)
	UExMa_WeaponAttributes* GetWeaponAttributes() const { return Attributes; };

	UFUNCTION(BlueprintCallable)
	UWeaponDataAsset* GetWeaponData() const { return WeaponData; };

	UFUNCTION(BlueprintCallable)
	UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystem; };

	UFUNCTION(BlueprintCallable)
	UAbilityContainer* GetAbilityContainer() const { return AbilityContainer; };

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWeaponDataAsset* WeaponData;

	UPROPERTY(VisibleDefaultsOnly, Category = Abilities)
	UAbilitySystemComponent* AbilitySystem;

	UPROPERTY(VisibleDefaultsOnly, Category = Abilities)
	UAbilityContainer* AbilityContainer;

	UPROPERTY(VisibleDefaultsOnly, Category = Abilities)
	UExMa_WeaponAttributes* Attributes;

	UPROPERTY()
	AActor* WeaponOwner = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly, Category = Montage)
	UAnimMontage* FireMontage;

	UPROPERTY(BlueprintReadOnly, Category = Montage)
	UAnimMontage* ReloadMontage;
};
