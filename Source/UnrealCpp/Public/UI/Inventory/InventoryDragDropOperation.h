// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Data/ItemDataAsset.h"
#include "InventoryDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UInventoryDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Slot")
	int32 StartIndex = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Slot")
	TWeakObjectPtr<UItemDataAsset> ItemData = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Slot")
	int32 Count = 0;


};
