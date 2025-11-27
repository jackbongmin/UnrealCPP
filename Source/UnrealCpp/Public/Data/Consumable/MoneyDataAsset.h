// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ConsumableDataAsset.h"
#include "MoneyDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UMoneyDataAsset : public UConsumableDataAsset
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 Money = 100;


	virtual void Excute(AActor* InTarget) const override;

};
