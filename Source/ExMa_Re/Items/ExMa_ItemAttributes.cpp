// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ExMa_ItemAttributes.h"

void UExMa_ItemAttributes::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

float UExMa_ItemAttributes::GetAttribute(const EItemAttributeType ItemAttributeType) const
{
    switch (ItemAttributeType)
    {
    case EItemAttributeType::Health:
        return Health.GetCurrentValue();
    case EItemAttributeType::MaxHealth:
        return MaxHealth.GetCurrentValue();
    case EItemAttributeType::Type:
        return Type.GetCurrentValue();
    case EItemAttributeType::Weight:
        return Weight.GetCurrentValue();
    case EItemAttributeType::Cost:
        return Cost.GetCurrentValue();
    }

	return 0.0f;
}
