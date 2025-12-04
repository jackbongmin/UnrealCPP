// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainHudWidget.h"
#include "Player/ActionCharacter.h"
#include "Player/ResourceComponent.h"
#include "UI/ResourceBarWidget.h"
#include "UI/Shop/ShopWidget.h"

void UMainHudWidget::NativeConstruct()
{
	CloseInventory();
	AActionCharacter* player = Cast<AActionCharacter>(GetOwningPlayerPawn());
	if (player)
	{

		if (UResourceComponent* resource = player->GetResourceComponent())
		{
			resource->OnHealthChanged.AddUObject(HealthBar.Get(), &UResourceBarWidget::RefreshWidget);
			resource->OnStaminaChanged.AddDynamic(StaminaBar.Get(), &UResourceBarWidget::RefreshWidget);

			HealthBar->RefreshWidget(resource->GetCurrentHealth(), resource->GetMaxHealth());
			StaminaBar->RefreshWidget(resource->GetCurrentStamina(), resource->GetMaxStamina());
		}
	}

	if (Inventory && Shop)
	{
		FScriptDelegate sellDelegate;
		sellDelegate.BindUFunction(Inventory, "CloseDetailInfo");
		Shop->AddToItemSellDelegate(sellDelegate);
	}


}

void UMainHudWidget::OpenInventory()
{
	Inventory->RefreshInventoryWidget();	// 열릴때마다 ui 내용 갱신
	Inventory->SetVisibility(ESlateVisibility::Visible);
	OpenState = EOpenState::Open;
}

void UMainHudWidget::CloseInventory()
{
	OpenState = EOpenState::Close;
	Inventory->SetVisibility(ESlateVisibility::Hidden);
}
