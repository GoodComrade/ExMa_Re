// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "WheeledVehiclePawn.h"
#include "ExMa_Re/ConfigStruct/VehicleConfigs/VehicleConfigStruct.h"
#include "ExMa_Re/UI/ExMaHUD.h"
#include "Components/SphereComponent.h"
#include "ExMa_RePawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UChaosWheeledVehicleMovementComponent;
class UExMa_VehicleAttributes;
class UInventoryComponent;
class AChestActor;
class AExMa_GameState;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateVehicle, Log, All);
/**
 *  Vehicle Pawn class
 *  Handles common functionality for all vehicle types,
 *  including input handling and camera management.
 *  
 *  Specific vehicle configurations are handled in subclasses.
 */
UCLASS()
class AExMa_RePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	AExMa_RePawn();

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	virtual void Tick(float Delta) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	float MaxCameraPitch = -60.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	float MinCameraPitch = 35.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	float CameraSensivity = 1;

	//UFUNCTION(BlueprintImplementableEvent)
	//FInteractionDispatcher OnChangeInteractedActor;

private:
	UPROPERTY()
	AExMaHUD* HUD;

	AExMa_GameState* GetGameState();

protected:
	virtual void BeginPlay() override;

	bool bIsPickingItems;

	UPROPERTY()
	TArray<AChestActor*> InterractedCrates;

	void ProcessPickupItems();

	void ProcessItemsOverflow(TArray<AChestActor*> ChestActorsToProcess);

	UPROPERTY(EditAnywhere, Category = Spawnable)
	TSubclassOf<AChestActor> ChestClass;

	void ProcessSpawnCrate();

	void ProcessTogglePickupState(bool NewState);

#pragma region Vehicle
protected:

	/** Steering Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SteeringAction;

	/** Throttle Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ThrottleAction;

	/** Brake Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* BrakeAction;

	/** Handbrake Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* HandbrakeAction;

	/** Look Around Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAroundAction;

	/** Toggle Camera Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ToggleCameraAction;

	/** Toggle Inventory Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ToggleInventoryAction;

	/** Reset Vehicle Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ResetVehicleAction;

	/** Keeps track of which camera is active */
	bool bFrontCameraActive = false;

#pragma endregion InputActions

#pragma region Vehicle
protected:

	/** Handles steering input */
	void Steering(const FInputActionValue& Value);

	/** Handles throttle input */
	void Throttle(const FInputActionValue& Value);

	/** Handles brake input */
	void Brake(const FInputActionValue& Value);

	/** Handles brake start/stop inputs */
	void StartBrake(const FInputActionValue& Value);
	void StopBrake(const FInputActionValue& Value);

	/** Handles handbrake start/stop inputs */
	void StartHandbrake(const FInputActionValue& Value);
	void StopHandbrake(const FInputActionValue& Value);

	/** Handles look around input */
	void LookAround(const FInputActionValue& Value);

	/** Handles toggle camera input */
	void ToggleCamera(const FInputActionValue& Value);

	/** Handles toggle inventory input */
	void ToggleInventory(const FInputActionValue& Value);

	/** Handles reset vehicle input */
	void ResetVehicle(const FInputActionValue& Value);

	/** Called when the brake lights are turned on or off */
	UFUNCTION(BlueprintImplementableEvent, Category = "Vehicle")
	void BrakeLights(bool bBraking);
#pragma endregion ActionBindings

#pragma region Vehicle

public:

	int GetHealth() const;
	int GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	UExMa_VehicleAttributes* GetAttributes();

	UPROPERTY(EditAnywhere, Category = Attributes)
	FName VehicleConfigRowName;

	UPROPERTY(EditAnywhere, Category = Attributes)
	UDataTable* DataTable;

protected:
	UPROPERTY(EditAnywhere, Category = Attributes)
	class UExMa_VehicleAttributes* Attributes;

	UFUNCTION()
	virtual void SetupVehicleAttributes();

	UFUNCTION(BlueprintCallable)
	virtual void ApplyVehicleAttributes();

#pragma endregion Attributes

#pragma region VehicleComponents
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USphereComponent* CollectSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* FrontSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FrontCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* BackSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* BackCamera;

	/** Character inventory component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;

	/** Inventory component to drop items from main inventory */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* OutInventoryComponent;

	/** Cast pointer to the Chaos Vehicle movement component */
	TObjectPtr<UChaosWheeledVehicleMovementComponent> ChaosVehicleMovement;
#pragma endregion Pointers

#pragma region VehicleComponents
public:
	FORCEINLINE USpringArmComponent* GetFrontSpringArm() const { return FrontSpringArm; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FrontCamera; }
	FORCEINLINE USpringArmComponent* GetBackSpringArm() const { return BackSpringArm; }
	FORCEINLINE UCameraComponent* GetBackCamera() const { return BackCamera; }
	FORCEINLINE const TObjectPtr<UChaosWheeledVehicleMovementComponent>& GetChaosVehicleMovement() const { return ChaosVehicleMovement; }

	UFUNCTION()
	UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; };

	UFUNCTION()
	UInventoryComponent* GetOutInventoryComponent() const { return OutInventoryComponent; };
#pragma endregion Getters

#pragma region VehicleComponents
protected:
	//TODO: show player pickup UI hint with binded hotkey instead of straigth pickup
	UFUNCTION()
	void OnCollectSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCollectSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
#pragma endregion Bindings
};
