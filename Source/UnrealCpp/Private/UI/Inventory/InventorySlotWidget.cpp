// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventorySlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Player/InventoryComponent.h"
#include "UI/Inventory/InventoryDragDropOperation.h"



void UInventorySlotWidget::InitializeSlot(UInventoryComponent* InInventoryComponent, int32 InIndex)
{
	if (InInventoryComponent)
	{

		TargetInventory = InInventoryComponent;
		Index = InIndex;
		SlotData = InInventoryComponent->GetSlotData(InIndex);
		OnSlotRightClick.BindUFunction(TargetInventory.Get(), "UseItem");	// 인벤토리 컴포넌트에 있는 UseItem과 바인딩

		RefreshSlot();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InInventoryComponent가 nullptr입니다."));
	}

}

void UInventorySlotWidget:: UInventorySlotWidget::RefreshSlot() const
{
	if (SlotData && !SlotData->IsEmpty())
	{
		// 슬롯에 아이템이 들어있으면 들어있는 아이템 보여주기
		ItemIconImage->SetBrushFromTexture(SlotData->ItemData->ItemIcon);
		ItemIconImage->SetBrushTintColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));

		CountText->SetText(FText::AsNumber(SlotData->GetCount()));
		MaxCountText->SetText(FText::AsNumber(SlotData->ItemData->ItemMaxStackCount));
	
		CountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		SeparateText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		MaxCountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		// 슬롯에 아이템이 없으면 빈슬롯 보여주기
		ClearSlotWidget();
	}
}

void UInventorySlotWidget::ClearSlotWidget() const
{
	ItemIconImage->SetBrushFromTexture(nullptr);
	ItemIconImage->SetBrushTintColor(FLinearColor::Transparent);
	CountText->SetVisibility(ESlateVisibility::Hidden);
	SeparateText->SetVisibility(ESlateVisibility::Hidden);
	MaxCountText->SetVisibility(ESlateVisibility::Hidden);



}

void UInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);	
	
	UInventoryDragDropOperation* DragOp = NewObject<UInventoryDragDropOperation>();
	DragOp->Index = Index;
	DragOp->ItemData = SlotData->ItemData;
	DragOp->Count = SlotData->GetCount();

	OutOperation = DragOp;
}

bool UInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	// 드래그 앤 드롭이 끝났다.
	UInventoryDragDropOperation* invenOp = Cast<UInventoryDragDropOperation>(InOperation);
	if (invenOp)
	{
		TargetInventory->SetItemAtIndex(Index, invenOp->ItemData.Get(), invenOp->Count);

		return true;	// 성공적으로 끝났음을 알림
	}
	return false;		// 실패로 끝났음을 알림 -> NativeOnDragCancelled 실행
}

void UInventorySlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	// 드래그 앤 드롭이 실패로 끝났다.
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
	UInventoryDragDropOperation* invenOp = Cast<UInventoryDragDropOperation>(InOperation);
	if (invenOp)
	{

	}

}

FReply UInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))		// 마우스 오른쪽 버튼 눌렸는지 확인
	{
	
		if (!SlotData->IsEmpty())		// 아이템이 있으면
		{
			UE_LOG(LogTemp, Log, TEXT("Widget %d Slot : Right Click(%s)"), Index, *SlotData->ItemData->ItemName.ToString());
			OnSlotRightClick.ExecuteIfBound(Index);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Widget %d Slot : Right Click(empty)"), Index);
		}
		return FReply::Handled();	// 이 마우스 클릭은  완료되었다라고 전달
	}
	else if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))		// 마우스 왼쪽 버튼 눌렸는지 확인
	{
		if (SlotData->ItemData)
		{
			return FReply::Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
		}
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);	// 나는 처리 안했다. 부모 or 다른 위젯이 처리할거다.
}
