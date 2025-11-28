// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickupItem.h"
#include "Player/InventoryOwner.h"


void APickupItem::OnPickupComplete_Implementation()
{
	// 자신을 먹은 대상에게 자기가 가지고 있는 무기를 알려줘야 함
	if (PickupOwner.IsValid() && PickupOwner->Implements<UInventoryOwner>())
	{
		IInventoryOwner::Execute_AddItem(PickupOwner.Get(), PickupItem, ItemCount);
	}


	Super::OnPickupComplete_Implementation();	// 자기 자신을 삭제시키기 때문에 마지막에 처리



}
