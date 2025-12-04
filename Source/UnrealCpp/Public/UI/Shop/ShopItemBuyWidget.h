// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopItemBuyWidget.generated.h"


class UImage;
class UTextBlock;
class UEditableTextBox;
class UButton;
class UOverlay;
/**
 * 
 */
UCLASS()
class UNREALCPP_API UShopItemBuyWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnItemCountTextChanged(const FText& Text);

	UFUNCTION()
	void OnItemCountTextCommitted(const FText& Text, ETextCommit::Type ComitMethod);


protected:
	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSell", meta = (BindWidget))
	TObjectPtr<UImage> ItemIcon = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSell", meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemName = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSell", meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemPrice = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSell", meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemStockCount = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSell", meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemDescription = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSell", meta = (BindWidget))
	TObjectPtr<UEditableTextBox> ItemCount = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSell", meta = (BindWidget))
	TObjectPtr<UButton> ItemBuy = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Shop|ItemSell", meta = (BindWidget))
	TObjectPtr<UOverlay> SoldOut = nullptr;

private:
	const int32 MinimumItemCount = 1;

};
