#include "ExMaGameplayTags.h"

namespace ExMaGameplayTags
{
	// Abilities
	UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Damage, "Ability.Damage");
	UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Damage_Decrease, "Ability.Damage.Decrease");
	UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Damage_Factor, "Ability.Damage.Factor");
	UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_ReloadTime, "Ability.ReloadTime");
	UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Cost, "Ability.Cost");
	UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_MagazineSize, "Ability.MagazineSize");
	UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_BulletsCount, "Ability.BulletsCount");
	UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Cooldown_PrimaryAttack, "Ability.Cooldown.PrimaryAttack");

	//AbilitiyDamageTypes
	UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Damage_Bullet, "Ability.DamageType.Bullet");
	UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Damage_Explosion, "Ability.DamageType.Explosion");
	UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Damage_Energy, "Ability.DamageType.Energy");

	//DamageTypes
	UE_DEFINE_GAMEPLAY_TAG(TAG_Damage_Bullet, "DamageType.Bullet");
	UE_DEFINE_GAMEPLAY_TAG(TAG_Damage_Explosion, "DamageType.Explosion");
	UE_DEFINE_GAMEPLAY_TAG(TAG_Damage_Energy, "DamageType.Energy");

	//ItemTypes
	UE_DEFINE_GAMEPLAY_TAG(TAG_Item_Cargo, "Item.Cargo");
	UE_DEFINE_GAMEPLAY_TAG(TAG_Item_Weapon, "Item.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(TAG_Item_Vehicle_Upgrade, "Item.Vehicle.Upgrade");
	UE_DEFINE_GAMEPLAY_TAG(TAG_Item_Vehicle_Reinforce, "Item.Vehicle.Reinforce");

	//WeaponTypes
	UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponType_LightMachineGun, "WeaponType.LightMachineGun");
	UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponType_MediumMachineGun, "WeaponType.MediumMachineGun");
	UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponType_HeavyMachineGun, "WeaponType.HeavyMachineGun");
	UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponType_LightArtilery, "WeaponType.LightArtilery");
	UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponType_MediumArtilery, "WeaponType.MediumArtilery");
	UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponType_SideArtilery, "WeaponType.SideArtilery");
	UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponType_LightShotgun, "WeaponType.LightShotgun");
	UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponType_MediumShotgun, "WeaponType.MediumShotgun");
	UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponType_RocketLauncher, "WeaponType.RocketLauncher");
	UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponType_SideRocketLauncher, "WeaponType.SideRocketLauncher");
	UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponType_Canon, "WeaponType.Canon");
	UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponType_LightPlasmaGun, "WeaponType.LightPlasmaGun");
	UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponType_MediumPlasmaGun, "WeaponType.MediumPlasmaGun");
	UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponType_PlasmaCanon, "WeaponType.PlasmaCanon");

	// Status
	UE_DEFINE_GAMEPLAY_TAG(TAG_Status_Death, "Status.Death");

	// Weapon
	UE_DEFINE_GAMEPLAY_TAG(TAG_Weapon, "Weapon");

	// WeaponGroups
	UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponGroup_One, "WeaponGroup.One");
	UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponGroup_Two, "WeaponGroup.Two");
	UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponGroup_Three, "WeaponGroup.Three");
	UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponGroup_Four, "WeaponGroup.Four");
	UE_DEFINE_GAMEPLAY_TAG(TAG_WeaponGroup_Five, "WeaponGroup.Five");
}
