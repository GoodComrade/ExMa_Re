// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Texture2D.h"
#include "DestroyedPart.generated.h"

class UStaticMeshComponent;
class UStaticMesh;

UCLASS()
class EXMA_RE_API ADestroyedPart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroyedPart();

	UFUNCTION(BlueprintCallable)
	void Init(UStaticMesh* MeshToSet, FVector ImpulseOrigin, UTexture2D* InDeathTexture);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* DestroyedPartMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
