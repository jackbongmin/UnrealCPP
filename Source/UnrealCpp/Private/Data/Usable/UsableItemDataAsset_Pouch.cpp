// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Usable/UsableItemDataAsset_Pouch.h"
#include "Player/InventoryOwner.h"

void UUsableItemDataAsset_Pouch::UseItem_Implementation(AActor* InTarget)
{
	if (InTarget->Implements<UInventoryOwner>())
	{
		int32 gold = FMath::RandRange(MinGold, MaxGold);
		IInventoryOwner::Execute_AddMoney(InTarget, gold);
	}
}
