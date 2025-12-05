// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct() override;

public:
	void AddToItemSellDelegate(const FScriptDelegate& Delegate);

protected:

	void ResetShopItemListWidget();


protected:
	UPROPERTY(BlueprintReadOnly, Category = "Shop|Sell", meta = (BindWidget))
	TObjectPtr<class UShopItemSellWidget> ItemSellWidget;
	
	UPROPERTY(BlueprintReadOnly, Category = "Shop|Buy", meta = (BindWidget))
	TObjectPtr<class UShopItemListWidget> ItemListWidget = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "Shop", meta = (BindWidget))
	TObjectPtr<class UButton> Exit;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop|Buy")
	TWeakObjectPtr<UDataTable> ShopItemList = nullptr;



};
