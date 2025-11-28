// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Pickup.h"
#include "PickupItem.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API APickupItem : public APickup
{
	GENERATED_BODY()
	
public:
	virtual void OnPickupComplete_Implementation() override;

protected:
	// 이 픽업을 먹었을 때 얻을 아이템
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Item")
	EItemCode PickupItem = EItemCode::Figure;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Item")
	int32 ItemCount = 1;



};
