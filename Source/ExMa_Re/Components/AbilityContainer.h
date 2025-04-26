// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayAbilitySpecHandle.h"
#include "AbilityContainer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXMA_RE_API UAbilityContainer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityContainer();

	bool CastPrimaryAttack();

	void CastReload();

	bool bCanCastAbilities{ true };

	void InitComponent();

    void SetAbilities(TSubclassOf<class UGameplayAbility> InPrimaryAttack, 
                      TSubclassOf<class UGameplayAbility> InReload);
    void InitAbilities();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
    TSubclassOf<class UGameplayAbility> PrimaryAttack;

    TSubclassOf<class UGameplayAbility> Reload;

private:
    FGameplayAbilitySpecHandle PrimaryAttackHandle;

    FGameplayAbilitySpecHandle ReloadHandle;

    UPROPERTY()
    class UAbilitySystemComponent* AbilitySystem;
};
