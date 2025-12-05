// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopItemListWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UShopItemListWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;


public:
	void ResetItemList(UDataTable* ItemList);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UVerticalBox> ItemBuyContainer;

	UPROPERTY(BlueprintReadOnly)
	TArray<class UShopItemBuyWidget*> ShopItems;

};
