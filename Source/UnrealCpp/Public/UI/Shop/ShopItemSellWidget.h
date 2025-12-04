// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopItemSellWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemSell);


/**
 * 
 */
UCLASS()
class UNREALCPP_API UShopItemSellWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FOnItemSell OnItemSell;

protected:
	// 드래그 완료
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

};
