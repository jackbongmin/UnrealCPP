// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Pickup.h"
#include "Data/ConsumableDataAsset.h"
#include "PickupComsumable.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API APickupComsumable : public APickup
{
	GENERATED_BODY()
	
public:
	virtual void OnPickupComplete_Implementation() override;


protected:
	virtual void OnConsume();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	TObjectPtr<UConsumableDataAsset> DataAsset = nullptr;

};
