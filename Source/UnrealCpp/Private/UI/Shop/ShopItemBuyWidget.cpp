// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Shop/ShopItemBuyWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/EditableTextBox.h"
#include "Components/Overlay.h"
#include "Components/Button.h"
#include "Data/ItemDataAsset.h"
#include "Player/InventoryOwner.h"


void UShopItemBuyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ItemCount)
	{
		ItemCount->SetHintText(FText::AsNumber(MinimumItemCount));
		ItemCount->OnTextChanged.AddDynamic(this, &UShopItemBuyWidget::OnItemCountTextChanged);		// 변경이 있을 때
		ItemCount->OnTextCommitted.AddDynamic(this, &UShopItemBuyWidget::OnItemCountTextCommitted);	// 변경을 확정했을 때(엔터친 후, 포커스를 잃은 후)
	}
}

void UShopItemBuyWidget::OnItemCountTextChanged(const FText& Text)
{
	UE_LOG(LogTemp, Log, TEXT("Changed : %s"), *Text.ToString());

	FString number = Text.ToString();

	if (number.IsNumeric())
	{
		int32 count = FCString::Atoi(*number);
		ItemCount->SetText(FText::AsNumber(count));
	}
}

void UShopItemBuyWidget::OnItemCountTextCommitted(const FText& Text, ETextCommit::Type ComitMethod)
{
	UE_LOG(LogTemp, Log, TEXT("Committed : %s"), *Text.ToString());

	FString number = Text.ToString();
	if (number.IsNumeric())
	{
		int32 count = FCString::Atoi(*number);
		ItemCount->SetText(FText::AsNumber(count));
	}
	else
	{
		ItemCount->SetText(FText::AsNumber(MinimumItemCount));
	}
}
