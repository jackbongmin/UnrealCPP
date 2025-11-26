// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Item/Pickup.h"
#include "PickupFactorySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UPickupFactorySubsystem : public UWorldSubsystem
{
	GENERATED_BODY()


public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category = "Pickup Factory")
	APickup* SpawnPickup(EItemCode InCode, FVector InLocation = FVector::ZeroVector, FRotator InRotator = FRotator::ZeroRotator);	// 파라메터 : 종류, 위치, 회전


private:
	
	void LoadPickupClassesMap();

	UPROPERTY()
	TMap<EItemCode, TSubclassOf<APickup>> PickupClasses;

};
