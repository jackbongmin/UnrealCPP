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
	if (!PlayerController)
	{
		PlayerController = GetWorld()->GetFirstPlayerController();
	}
	FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	UE_LOG(LogTemp, Log, TEXT("Mouse : %s"), *MousePosition.ToString());
	CanvasSlot->SetPosition(MousePosition - ParentPosition);

	

	//FVector2D MousePosition;
	//if (UWidgetLayoutLibrary::GetMousePositionScaledByDPI(PlayerController, MousePosition.X, MousePosition.Y))
	//{
	//	UE_LOG(LogTemp, Log, TEXT("Mouse : %s"), *MousePosition.ToString());
	//	CanvasSlot->SetPosition(MousePosition);
	//}
}
