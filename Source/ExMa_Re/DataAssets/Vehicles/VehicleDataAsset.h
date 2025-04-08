#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ExMa_Re/Enums/VehicleType.h"
#include "VehicleDataAsset.generated.h"

class AExMa_RePawn;

UCLASS()
class EXMA_RE_API UVehicleDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
    TSubclassOf<AExMa_RePawn> GetPawnClass() { return VehicleClass; }

public:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    EVehicleType VehicleType = EVehicleType::NONE;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float Health = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float MaxHealth = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float Armor = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float MaxArmor = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float Weight = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float MaxWeight = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float BulletResistance = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float ExplosionResistance = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float EnergyResistance = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int32 Cost = 0;

protected:
    //TODO: implement AExMa_RePawn class & set their static version here 
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<AExMa_RePawn> VehicleClass;
};
