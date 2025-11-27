// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ConsumableDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class UNREALCPP_API UConsumableDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	// 대상에게 자신의 정보를 기반으로 영향을 주는 함수
	UFUNCTION(BlueprintCallable, Category = "Pickup|Consumable")
	virtual void Excute(AActor* InTarget) const {};




};
