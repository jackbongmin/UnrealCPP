// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player/InventoryComponent.h"
#include "InventorySlotWidget.generated.h"

//struct FInvenSlot;
//class UInventoryComponent;

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSlotClicked, int32, InSlotIndex);

/**
 * 
 */
UCLASS()
class UNREALCPP_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 이 위젯이 보여줄 데이터를 세팅
	void InitializeSlot(class UInventoryComponent* InInventoryComponent, int32 InIndex);




	// 설정된 데이터를 기반으로 위젯에서 표시하는 내용을 갱신
	void RefreshSlot() const;

protected:
	void ClearSlotWidget() const;


	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;


	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	FOnSlotClicked OnSlotRightClick;
	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|IventorySlot", meta = (BindWidget))
	TObjectPtr<class UImage> ItemIconImage = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|IventorySlot", meta = (BindWidget))
	TObjectPtr<class UTextBlock> CountText = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|IventorySlot", meta = (BindWidget))
	TObjectPtr<class UTextBlock> SeparateText = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|IventorySlot", meta = (BindWidget))
	TObjectPtr<class UTextBlock> MaxCountText = nullptr;

private:
	int32 Index = -1;

	FInvenSlot* SlotData = nullptr;		// 구조체는 TWeakObjectPtr이 인식을 못하는것 같아서 별도 처리

	UPROPERTY()
	TWeakObjectPtr<UInventoryComponent> TargetInventory = nullptr;

};