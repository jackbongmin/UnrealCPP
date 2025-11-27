// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Consumable/MoneyDataAsset.h"
#include "Player/InventoryOwner.h"


void UMoneyDataAsset::Excute(AActor* InTarget) const
{
	if (InTarget && InTarget->Implements<UInventoryOwner>())	// 대상이 인벤토리를 가지고 있으면
	{
		IInventoryOwner::Execute_AddMoney(InTarget, Money);		// 돈을 추가해라
	}
}
