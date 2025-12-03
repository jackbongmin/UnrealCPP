// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ItemDataAsset.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FInvenSlot
{
	GENERATED_BODY()

public:

	// 이 슬롯에 들어있는 아이템의 종류
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Slot")
	TObjectPtr<UItemDataAsset> ItemData = nullptr;

	// 헬퍼
	// 이 슬롯이 비어있는지 확인하는 함수
	bool IsEmpty() const { return ItemData == nullptr || Count < 1; }
	// 이 슬롯이 가득차있는지 확인하는 함수
	bool IsFull() const { return ItemData && Count >= ItemData->ItemMaxStackCount; }
	// 슬롯을 비우는 함수
	void Clear()
	{
		ItemData = nullptr;
		Count = 0;
	}

	// Getter/Setter
	int32 GetCount() const { return Count; }
	void SetCount(int32 NewCount){
		if (ItemData && NewCount > 0)
		{
			Count = FMath::Min(NewCount, ItemData->ItemMaxStackCount);	//NewCount는 0~ItemMaxStakCount 범위의 값
		}
		else
		{
			Clear();
		}
	}

protected:

	// 이 슬롯에 아이템이 몇개 스택되어 있는지 기록
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory|Slot")
	int32 Count = 0;

};


DECLARE_DYNAMIC_DELEGATE_OneParam(FOnInventorySlotChanged, int32, InIndex);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnInventoryMoneyChanged, int32, CurrentMoney);

// 여러개의 아이템 슬롯을 가진다.
// 하나의 슬롯에는 한종류의 아이템만 들어간다.
// 아이템 종류에 따라 한 슬롯에 중첩될 수 있는 아이템 갯수가 달라질 수 있다.

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCPP_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	// 각종 함수가 실패했을 때 리턴하는 상수
	static const int32 InventoryFail = -1;

	// 인벤토리에서 특정 슬롯에 변화가 있었을 때 호출되는 델리게이트
	FOnInventorySlotChanged OnInventorySlotChanged;

	// 인벤토리 내의 금액 변화가 있을 때 호출되는 델리게이트
	FOnInventoryMoneyChanged OnInventoryMoneyChanged;

public:	

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddMoney(int32 InIncome);


	// 아이템을 추가하는 함수(리턴:먹고 남은 아이템의 수, InItemData: 추가되는 아이템의 종류, InCount : 추가되는 아이템의 갯수)
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 AddItem(UItemDataAsset* InItemData, int32 InCount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UseItem(int32 InUseIndex);


	// 특정칸에 있는 아이템의 갯수를 조절하는 함수(증가/감소)
	// InSlotIndex : 변경할 슬롯, InDeltaCount : 변화량
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UpdateSlotCount(int32 InSlotIndex, int32 InDeltaCount = -1);

	// 특정칸을 비우는 함수(InSlotIndex : 비울 슬롯)
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ClearSlotIndex(int32 InSlotIndex);


	// 아이템을 특정칸에 추가하는 함수(초기화, 로딩 등에 사용)
	// InSlotIndex : 아이템이 추가될 슬롯, InItemData: 추가되는 아이템의 종류, InCount : 추가되는 아이템의 갯수
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItemAtIndex(int32 InSlotIndex, UItemDataAsset* InItemData, int32 InCount);

	// 특정 슬롯을 확인하기 위한 함수. 읽기 전용(InSlotIndex : 확인할 슬롯)	
	FInvenSlot* GetSlotData(int32 InSlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	inline bool IsValidIndex(int32 InSlotIndex) const {
		return InSlotIndex < InventorySize && InSlotIndex >= 0;
	}

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	inline int32 GetInventorySize() const { return InventorySize; }


protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 InventorySize = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory|Money")
	int32 Money = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory|Slot")
	TArray<FInvenSlot> Slots;



private:
	

	
	// 같은 종류의 아이템이 슬롯을 찾는 함수	
	// InItemData : 비교할 아이템의 종류, InStartIndex : 찾기 시작할 인덱스
	int32 FindSlotWithItem(UItemDataAsset* InItemData, int32 InStartIndex = 0);

	// 비어있는 슬롯을 찾는 함수
	int32 FindEmptySlot();


};
