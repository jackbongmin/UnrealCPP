// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Usable/UsableItemDataAsset.h"
#include "UsableItemDataAsset_Pouch.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UUsableItemDataAsset_Pouch : public UUsableItemDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData|GoldPouch", meta = (ClampMin = "0"))
	int32 MinGold = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData|GoldPouch", meta = (ClampMin = "0"))
	int32 MaxGold = 1000;

public:
	virtual void UseItem_Implementation(AActor* InTarget) override;

};
