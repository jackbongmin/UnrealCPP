// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryWidget.h"
#include "UI/Inventory/InventorySlotWidget.h"
#include "UI/Inventory/GoldPanelWidget.h"
#include "UI/Inventory/InventoryDragDropOperation.h"
#include "UI/Inventory/DetailInfoWidget1.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Player/InventoryComponent.h"


void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnCloseClicked);
	}

	if (DetailInfoPanel)
	{
		UCanvasPanelSlot* canvasSlot = Cast<UCanvasPanelSlot>(Slot);
		DetailInfoPanel->SetParentPosition(canvasSlot->GetPosition());
	}
}


void UInventoryWidget::InitializeInventoryWidget(UInventoryComponent* InventoryComponent)
{

	if (DetailInfoPanel)
	{
		UCanvasPanelSlot* canvasSlot = Cast<UCanvasPanelSlot>(Slot);
		//UE_LOG(LogTemp, Log, TEXT("ParentPosition : %s"), *canvasSlot->GetPosition().ToString());
		DetailInfoPanel->SetParentPosition(canvasSlot->GetPosition());	// DetailInfoPanel에 인벤토리 위젯의 위치 알려주기
	}



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
				// 인벤토리 컴포넌트에 저장되어 있는 슬롯과 슬롯 위젯을 엮어주는 작업
				UInventorySlotWidget* slotWidget = Cast<UInventorySlotWidget>(SlotGridPanel->GetChildAt(i));
				slotWidget->InitializeSlot(TargetInventory.Get(), i);	

				slotWidget->OnSlotEnter.AddDynamic(this, &UInventoryWidget::OpenDetailInfo);
				slotWidget->OnSlotLeave.AddDynamic(this, &UInventoryWidget::CloseDetailInfo);

				SlotWidgets.Add(slotWidget);	// 연결이 끝난 슬롯을 SlotWidgets에 순서대로 저장
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
	if (invenOp)
	{
		TargetInventory->SetItemAtIndex(invenOp->StartIndex, invenOp->ItemData.Get(), invenOp->Count);
		return true;
	}
	return false;
}

void UInventoryWidget::OnCloseClicked()
{
	OnInventoryCloseRequested.Broadcast();	// 닫힘 버튼이 눌려졌음을 알리기만 함
}

void UInventoryWidget::OpenDetailInfo(int InSlotIndex)
{
	if (TargetInventory.IsValid())
	{
		DetailInfoPanel->Open(TargetInventory->GetSlotData(InSlotIndex)->ItemData);
		//DetailInfoPanel->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UInventoryWidget::CloseDetailInfo()
{
	//DetailInfoPanel->SetVisibility(ESlateVisibility::Hidden);
	DetailInfoPanel->Close();
}
