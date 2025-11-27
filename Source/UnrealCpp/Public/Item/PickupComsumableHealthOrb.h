// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/PickupComsumable.h"
#include "PickupComsumableHealthOrb.generated.h"

/**
 * 파생 클래스 예시
 */
UCLASS()
class UNREALCPP_API APickupComsumableHealthOrb : public APickupComsumable
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealOrb")
	float HealAmount = 30.0f;

protected:
	virtual void OnConsume() override;
	
};
