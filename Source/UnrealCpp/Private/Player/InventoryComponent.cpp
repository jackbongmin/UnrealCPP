// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/InventoryComponent.h"
#include "Data/Usable/UsableItem.h"



// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Slots.SetNum(InventorySize);	// 인벤토리 크기만큼 빈 슬롯 만들기
	// ...
}




void UInventoryComponent::AddMoney(int32 InIncome)
{
	Money += InIncome;
	OnInventoryMoneyChanged.ExecuteIfBound(Money);
}

int32 UInventoryComponent::AddItem(UItemDataAsset* InItemData, int32 InCount)
{
	// 1. 같은 종류의 아이템이 들어있는 슬롯이 있는지 찾기
	//  1.1 같은 종류의 아이템이 있으면 InCount만큼 추가를 시도
	//	1.2 추가하고 남은 아이템이 있으면 1번 반복
	//  1.3 추가하고 남은 아이템이 없으면 return 0; 하고 종료
	// 2. 같은 종류의 아이템이 없다면
	//  2.1 빈칸이 있는지 찾기
	//	2.2 빈칸이 있으면 빈칸에 아이템 추가 시도
	//  2.3 추가하고 남은 아이템이 있으면 2번 반복
	//	2.4 추가하고 남은 아이템이 없으면 return 0; 하고 종료
	// 3. 남아있는 InCount를 리턴하고 종료.

	int32 remainingCount = InCount;

	if (InItemData && InCount > 0)	// 추가가 가능할 때만 추가
	{

		// 같은 종류의 아이템이 들어있는 슬롯을 찾아 추가하기
		int32 startIndex = 0;
		
		while (remainingCount > 0)		// remainingCount가 남아있는한 반복(같은 종류의 슬롯이 없으면 break)
		{

			int32 foundIndex = FindSlotWithItem(InItemData, startIndex);	// 같은 종류의 아이템이 들어있고 공간에 여유가 있는 슬롯 찾기 시도
			if (foundIndex == UInventoryComponent::InventoryFail)
				break;		// 같은 종류의 아이템이 들어있는 슬롯이 없으면 "while (remainingCount > 0)"를 break

			// 같은 종류의 아이템이 들어있는 슬롯을 찾았다.
			FInvenSlot& slot = Slots[foundIndex];
			int32 availableCount = slot.ItemData->ItemMaxStackCount - slot.GetCount();	// 슬롯에 추가 가능한 갯수가 몇개인지 확인
			if (availableCount > 0)														// 추가가 가능하면
			{
				int32 amountToAdd = FMath::Min(availableCount, remainingCount);			// 추가량 결정
				SetItemAtIndex(foundIndex, InItemData, slot.GetCount() + amountToAdd);	// 결정된 추가량만큼 추가
				remainingCount -= amountToAdd;											// remainingCount를 슬롯에 추가한만큼 감소
			}
	
			startIndex = foundIndex + 1;	// FindSlotWithItem에서 현재 슬롯 다음부터 찾게 하기
		}

		// 같은 종류의 아이템이 들어있는 슬롯이 없으니 빈칸에 추가하기
		
		while (remainingCount > 0)		// remainingCount가 남아있는한 반복(빈슬롯이 없으면 break)
		{
			int32 emptyIndex = FindEmptySlot();
			if (emptyIndex == UInventoryComponent::InventoryFail)
				break;	// 빈슬롯이 없다.

			int32 amountToAdd = FMath::Min(InItemData->ItemMaxStackCount, remainingCount);	// 추가량 결정
			SetItemAtIndex(emptyIndex, InItemData, amountToAdd);							// 결정된 추가량만큼 추가
			remainingCount -= amountToAdd;													// remainingCount를 슬롯에 추가한만큼 감소
		}
		
		// 같은 종류의 아이템이 들어있는 슬롯과 빈슬롯이 모두 채우고도 남은 아이템이 있다. => remainingCount 리턴




	}

	return remainingCount;
}

void UInventoryComponent::UseItem(int32 InUseIndex)
{
	FInvenSlot* slot = GetSlotData(InUseIndex);
	if (slot->ItemData && slot->ItemData->Implements<UUsableItem>())
	{
		UE_LOG(LogTemp, Log, TEXT("Inven %d Slot : 사용됨"), InUseIndex);
		IUsableItem::Execute_UseItem(slot->ItemData, GetOwner());	// 이 컴포넌트를 가지고 있는 액터에게 아이템을 사용해라

		UpdateSlotCount(InUseIndex, -1);

	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Inven %d Slot : 비어있거나 사용할 수 없는 아이템"), InUseIndex);
	}
}

void UInventoryComponent::SetItemAtIndex(int32 InSlotIndex, UItemDataAsset* InItemData, int32 InCount)
{
	if (IsValidIndex(InSlotIndex))
	{
		FInvenSlot& TargetSlot = Slots[InSlotIndex];
		
		TargetSlot.ItemData = InItemData;
		TargetSlot.SetCount(InCount);	// InCount가 0이하면 자동 Clear

		OnInventorySlotChanged.ExecuteIfBound(InSlotIndex);

	}

}



void UInventoryComponent::UpdateSlotCount(int32 InSlotIndex, int32 InDeltaCount)
{
	if (IsValidIndex(InSlotIndex))
	{
		FInvenSlot& TargetSlot = Slots[InSlotIndex];
		if (TargetSlot.IsEmpty()) return;		// 슬롯이 비어있으면 변화할 수 없음

		int32 NewCount = TargetSlot.GetCount() + InDeltaCount;
		SetItemAtIndex(InSlotIndex, TargetSlot.ItemData, NewCount);

	}	
}

void UInventoryComponent::ClearSlotIndex(int32 InSlotIndex)
{
	//if (IsValidIndex(InSlotIndex))
	//{
	//	FInvenSlot& TargetSlot = Slots[InSlotIndex];
	//	TargetSlot.Clear();
	//	OnInventorySlotChanged.ExecuteIfBound(InSlotIndex);
	//}

	SetItemAtIndex(InSlotIndex, nullptr, 0);
}

FInvenSlot* UInventoryComponent::GetSlotData(int32 InSlotIndex)
{
	check(IsValidIndex(InSlotIndex));

	/*
	* check  : 거짓이면 프로그램 종료. shipping 빌드에 포함 안됨
	* verify : 거짓이면 프로그램 종료. shipping 빌드에 포함됨(검사는 안함)
	* ensure : 거짓이면 로그 출력하고 계속. shipping 빌드에 포함됨
	*/

	return &Slots[InSlotIndex];
}

int32 UInventoryComponent::FindSlotWithItem(UItemDataAsset* InItemData, int32 InStartIndex)
{
	int32 result = UInventoryComponent::InventoryFail;	// -1운 실패했음을 알리는 값
	int32 size = Slots.Num();
	for (int32 i = InStartIndex; i < size; i++)
	{
		if (Slots[i].ItemData == InItemData && !Slots[i].IsFull())	// 같은 데이터에셋을 가지고 있으면서 빈칸이 있는 경우
		{
			result = i;
			break;
		}
	}
	return result;
}

int32 UInventoryComponent::FindEmptySlot()
{
	int32 result = -1;	// -1운 실패했음을 알리는 값
	int32 size = Slots.Num();
	for (int32 i = 0; i < size; i++)
	{
		if (Slots[i].IsEmpty())
		{
			result = i;
			break;
		}
	}
	return result;
}



