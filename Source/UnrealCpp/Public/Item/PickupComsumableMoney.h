// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/PickupComsumable.h"
#include "PickupComsumableMoney.generated.h"

/**
 * 파생 클래스 예시
 */
UCLASS()
class UNREALCPP_API APickupComsumableMoney : public APickupComsumable
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 Money = 100;



protected:
	virtual void OnConsume() override;


};
