// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/TemporarySlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UTemporarySlot::SetItemIconImage(UTexture2D* InTexture)
{
	ItemIconImage->SetBrushFromTexture(InTexture);
}

void UTemporarySlot::SetCountText(int32 InCount)
{
	CountText->SetText(FText::AsNumber(InCount));
}
