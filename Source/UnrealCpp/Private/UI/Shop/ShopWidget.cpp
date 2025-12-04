// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Shop/ShopWidget.h"
#include "UI/Shop/ShopItemSellWidget.h"


void UShopWidget::AddToItemSellDelegate(const FScriptDelegate& Delegate)
{
	ItemSellWidget->OnItemSell.Add(Delegate);
}
