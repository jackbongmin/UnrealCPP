// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryCloseRequested);

/**
 * 
 */


UCLASS()
class UNREALCPP_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	void InitializeInventoryWidget(class UInventoryComponent* InventoryComponent);
	void RefreshInventoryWidget();
	
	UFUNCTION()
	void RefreshMoneyPanel(int32 CurrentMoney);
	
	UFUNCTION()
	void RefreshSlotWidget(int32 InSlotIndex);
	void ClearInventoryWidget();

	UPROPERTY(BlueprintAssignable, Category = "UI|Inventory")
	FOnInventoryCloseRequested OnInventoryCloseRequested;

protected:
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;


private:
	UFUNCTION()
	void OnCloseClicked();

	UFUNCTION(BlueprintCallable, Category = "UI|Inventory")
	inline bool IsValidIndex(int32 InSlotIndex) const {
		return InSlotIndex < SlotWidgets.Num() && InSlotIndex >= 0;
	};


protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> CloseButton = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUniformGridPanel> SlotGridPanel = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UGoldPanelWidget> GoldPanel = nullptr;

private:
	UPROPERTY()
	TWeakObjectPtr<UInventoryComponent> TargetInventory = nullptr;

	TArray<TObjectPtr<class UInventorySlotWidget>> SlotWidgets;
	
};
