#pragma once

#include "CoreMinimal.h"
#include "WeaponAttributeType.generated.h"

UENUM()
enum class EWeaponAttributeType : uint8
{
	Damage						UMETA(DisplayName = "Damage"),
	AttackCost					UMETA(DisplayName = "AttackCost"),
	Cooldown					UMETA(DisplayName = "Cooldown"),
	ReloadTime					UMETA(DisplayName = "ReloadTime"),
	Spread						UMETA(DisplayName = "Spread"),
	MaxBulletsCount				UMETA(DisplayName = "MaxBulletsCount"),
	MagazineSize				UMETA(DisplayName = "MagazineSize"),
	BurstSize					UMETA(DisplayName = "BurstSize"),
	BurstDelay					UMETA(DisplayName = "BurstDelay"),
	MaxRange					UMETA(DisplayName = "MaxRange"),
	MinBulletsInShot			UMETA(DisplayName = "MinBulletsInShot"),
	MaxBulletsInShot			UMETA(DisplayName = "MaxBulletsInShot"),
	Health						UMETA(DisplayName = "Health"),
	MaxHealth					UMETA(DisplayName = "MaxHealth"),
	AimType						UMETA(DisplayName = "AimType"),
	BlustRadius					UMETA(DisplayName = "BlustRadius"),
	AimTime						UMETA(DisplayName = "AimTime"),
};