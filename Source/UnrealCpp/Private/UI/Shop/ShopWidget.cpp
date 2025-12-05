// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Shop/ShopWidget.h"
#include "UI/Shop/ShopItemSellWidget.h"
#include "UI/Shop/ShopItemListWidget.h"


void UShopWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ResetShopItemListWidget();
}

void UShopWidget::AddToItemSellDelegate(const FScriptDelegate& Delegate)
{
	ItemSellWidget->OnItemSell.Add(Delegate);
}

void UShopWidget::ResetShopItemListWidget()
{
	if (ShopItemList.IsValid())
	{
		ItemListWidget->ResetItemList(ShopItemList.Get());
	}
}
