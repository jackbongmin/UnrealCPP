// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "DetailInfoWidget1.generated.h"



class UTextBlock;
class UImage;



/**
 * 
 */
UCLASS()
class UNREALCPP_API UDetailInfoWidget1 : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Open(class UItemDataAsset* InItemData);
	void Close();

	inline void SetParentPosition(const FVector2D& InPosition) { ParentPosition = InPosition; }

protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void SetInfo(class UItemDataAsset* InItemData);
	void UpdateLocation();
	


protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemDescriptionText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemPriceText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> ItemIconImage = nullptr;

private:

	UCanvasPanelSlot* CanvasSlot = nullptr;

	FVector2D ParentPosition;

};
