// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryWidget.h"
#include "UI/Inventory/InventorySlotWidget.h"
#include "UI/Inventory/GoldPanelWidget.h"
#include "UI/Inventory/InventoryDragDropOperation.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Player/InventoryComponent.h"


void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnCloseClicked);
	}



}


void UInventoryWidget::InitializeInventoryWidget(UInventoryComponent* InventoryComponent)
{
	if (InventoryComponent && SlotGridPanel)
	{
		TargetInventory = InventoryComponent;	// 인벤토리 컴포넌트 저장
		if (TargetInventory.IsValid())
		{
			UE_LOG(LogTemp, Log, TEXT("인벤토리 위젯 초기화"));

			if (SlotGridPanel->GetChildrenCount() != TargetInventory->GetInventorySize())
			{
				UE_LOG(LogTemp, Error, TEXT("인벤토리 컴포넌트와 위젯의 슬롯 크기가 다릅니다!!!"));
				return;
			}

			TargetInventory->OnInventoryMoneyChanged.BindUFunction(this, "RefreshMoneyPanel");
			TargetInventory->OnInventorySlotChanged.BindUFunction(this, "RefreshSlotWidget");

			RefreshMoneyPanel(0);

			int32 size = FMath::Min(SlotGridPanel->GetChildrenCount(), TargetInventory->GetInventorySize());
			SlotWidgets.Empty(size);
			for (int i = 0; i < size; i++)
			{
				FInvenSlot* slotData = TargetInventory->GetSlotData(i);
				UInventorySlotWidget* slotWidget = Cast<UInventorySlotWidget>(SlotGridPanel->GetChildAt(i));
				slotWidget->InitializeSlot(i, slotData);	// 인벤토리 컴포넌트에 저장되어 있는 슬롯과 슬롯 위젯을 엮어주는 작업
				slotWidget->OnSlotRightClick.Clear();
				slotWidget->OnSlotRightClick.BindUFunction(TargetInventory.Get(), "UseItem");
				SlotWidgets.Add(slotWidget);
			}
		}
	}
}

void UInventoryWidget::RefreshInventoryWidget()
{
	for (const UInventorySlotWidget* slot : SlotWidgets)
	{
		slot->RefreshSlot();
	}
}

void UInventoryWidget::RefreshMoneyPanel(int32 CurrentMoney)
{
	GoldPanel->SetGold(CurrentMoney);
}

void UInventoryWidget::RefreshSlotWidget(int32 InSlotIndex)
{
	UE_LOG(LogTemp, Log, TEXT("RefreshSlotWidget"));
	if (IsValidIndex(InSlotIndex))
	{
		SlotWidgets[InSlotIndex]->RefreshSlot();
	}
}

void UInventoryWidget::ClearInventoryWidget()
{
	TargetInventory = nullptr;
}

bool UInventoryWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UInventoryDragDropOperation* invenOp = Cast<UInventoryDragDropOperation>(InOperation);
	if (InOperation)
	{
		return true;
	}
}

void UInventoryWidget::OnCloseClicked()
{
	OnInventoryCloseRequested.Broadcast();	// 닫힘 버튼이 눌려졌음을 알리기만 함
}