// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Usable/UsableItemDataAsset.h"
#include "UsableItemDataAsset_StmPotion.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UUsableItemDataAsset_StmPotion : public UUsableItemDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemData|StaminaPotion")
	float RecoveryAmount = 20.0f;

public:
	virtual void UseItem_Implementation(AActor* InTarget) override;

};
