// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/DetailInfoWidget1.h"
#include "Data/ItemDataAsset.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"



void UDetailInfoWidget1::Open(UItemDataAsset* InItemData)
{
	SetInfo(InItemData);
	UpdateLocation();
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UDetailInfoWidget1::Close()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UDetailInfoWidget1::NativeConstruct()
{
	Super::NativeConstruct();
	
	
	CanvasSlot = Cast<UCanvasPanelSlot>(Slot);
}

void UDetailInfoWidget1::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateLocation();
}

void UDetailInfoWidget1::SetInfo(UItemDataAsset* InItemData)
{
	if (InItemData)
	{
		ItemNameText->SetText(InItemData->ItemName);
		ItemDescriptionText->SetText(InItemData->ItemDescription);
		ItemPriceText->SetText(FText::AsNumber(InItemData->ItemPrice));
		ItemIconImage->SetBrushFromTexture(InItemData->ItemIcon);
	}
}

void UDetailInfoWidget1::UpdateLocation()
{

	FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	// SetPosition은 부모의 원점 기준 위치 설정
	CanvasSlot->SetPosition(MousePosition - ParentPosition);	// 그래서 부모의 위치를 빼서 뷰포트 기준으로 원점 설정

}
