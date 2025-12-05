// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Shop/ShopItemListWidget.h"
#include "UI/Shop/ShopItemBuyWidget.h"
#include "Data/DataTableRows.h"
#include "Components/VerticalBox.h"

void UShopItemListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ItemBuyContainer)
	{
		int count = ItemBuyContainer->GetChildrenCount();
		ShopItems.Empty(count);
		for (int32 i = 0; i < count; i++)
		{
			UShopItemBuyWidget* itemWidget = Cast<UShopItemBuyWidget>(ItemBuyContainer->GetChildAt(i));
			ShopItems.Add(itemWidget);
		}
	}
}

void UShopItemListWidget::ResetItemList(UDataTable* ItemList)
{
	// 전체 가중치 계산
	float totalWeight = 0.0f;
	TArray<FShopData_TableRow*> allRows;
	ItemList->GetAllRows(TEXT("ShopDataTable"), allRows);
	for (const FShopData_TableRow* row : allRows)
	{
		totalWeight += row->SelectWeight;

		//ShopItems[index]->SetItemData(row->ItemData, row->StockCount);
		//index++;
	}

	// 가중치에 따라 ShopItems 갯수 만큼 데이터 ㅅ너택
	int32 selectCount = ShopItems.Num();
	TArray<const FShopData_TableRow*> selectedRows;
	selectedRows.Empty(selectCount);
	for (int i = 0; i < ShopItems.Num(); i++)
	{

		float hit = FMath::FRandRange(0.0f, totalWeight);
		float currentWeight = 0.0f;
		for (const FShopData_TableRow* row : allRows)
		{
			currentWeight += row->SelectWeight;
			if (hit < currentWeight)
			{
				selectedRows.Add(row);
				break;
			}
		}
	}

	// 선택된 데이터에 따라 UI갱신
	for (int32 i = 0; i < selectCount; i++)
	{
		const FShopData_TableRow* row = selectedRows[i];
		ShopItems[i]->SetItemData(row->ItemData, row->StockCount);
	}


}
