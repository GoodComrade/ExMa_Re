// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "ItemAttributeType.h"
#include "ExMa_ItemAttributes.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, Attribute)                                   \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Attribute);                                      \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Attribute);                                      \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Attribute);                                     \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, Attribute);

UCLASS()
class EXMA_RE_API UExMa_ItemAttributes : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    UPROPERTY(BlueprintReadOnly, Category = Item)
    FGameplayAttributeData Type;
    ATTRIBUTE_ACCESSORS(UExMa_ItemAttributes, Type);

    UPROPERTY(BlueprintReadOnly, Category = Item)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UExMa_ItemAttributes, Health);

    UPROPERTY(BlueprintReadOnly, Category = Item)
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UExMa_ItemAttributes, MaxHealth);

    UPROPERTY(BlueprintReadOnly, Category = Item)
    FGameplayAttributeData Weight;
    ATTRIBUTE_ACCESSORS(UExMa_ItemAttributes, Weight);

    UPROPERTY(BlueprintReadOnly, Category = Item)
    FGameplayAttributeData Cost;
    ATTRIBUTE_ACCESSORS(UExMa_ItemAttributes, Cost);

    UFUNCTION(BlueprintCallable)
    float GetAttribute(EItemAttributeType ItemAttributeType) const;
};
