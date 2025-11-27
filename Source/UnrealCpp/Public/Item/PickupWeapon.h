// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Pickup.h"
#include "PickupWeapon.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API APickupWeapon : public APickup
{
	GENERATED_BODY()
	
public:
	virtual void OnPickupComplete_Implementation() override;

	inline void SetWeaponUseCount(int32 InCount) { UseCount = InCount; };

protected:
	// 이 픽업을 먹었을 때 얻을 무기 아이템
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Weapon")
	EWeaponCode PickupWeapon = EWeaponCode::BasicFinger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Weapon")
	int32 UseCount = 1;

};
