// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponActor.h"
#include "ConsumableWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponUseEnded);
/**
 * 
 */
UCLASS()
class UNREALCPP_API AConsumableWeapon : public AWeaponActor
{
	GENERATED_BODY()

public:
	virtual void OnAttack() override;
	virtual void OnWeaponPickuped(AActionCharacter* InOwner) override;
	virtual bool CanAttack() override { return RemaingUseCount > 0; }

	//void Weapon

protected:

	// 최대 사용횟수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	int32 MaxUseCount = 10;

	// 남은 사용 횟수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 RemaingUseCount = 10;

	UPROPERTY(BlueprintAssignable, BlueprintReadOnly, Category = "Weapon")
	FOnWeaponUseEnded OnWeaponUseEnded;

};
