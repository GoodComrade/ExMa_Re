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

    UPROPERTY(BlueprintReadOnly, Category = Character)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UExMa_ItemAttributes, Health);

    UPROPERTY(BlueprintReadOnly, Category = Character)
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UExMa_ItemAttributes, MaxHealth);

    UPROPERTY(BlueprintReadOnly, Category = Character)
    FGameplayAttributeData Size;
    ATTRIBUTE_ACCESSORS(UExMa_ItemAttributes, Size);

    UPROPERTY(BlueprintReadOnly, Category = Character)
    FGameplayAttributeData Type;
    ATTRIBUTE_ACCESSORS(UExMa_ItemAttributes, Type);

    UPROPERTY(BlueprintReadOnly, Category = Character)
    FGameplayAttributeData Weight;
    ATTRIBUTE_ACCESSORS(UExMa_ItemAttributes, Weight);

    UFUNCTION(BlueprintCallable)
    float GetAttribute(EItemAttributeType ItemAttributeType) const;
};
