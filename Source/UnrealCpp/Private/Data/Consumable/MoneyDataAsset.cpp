// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Consumable/MoneyDataAsset.h"
#include "Player/InventoryOwner.h"


void UMoneyDataAsset::Excute(AActor* InTarget) const
{
	if (InTarget && InTarget->Implements<UInventoryOwner>())
	{
		IInventoryOwner::Execute_AddMoney(InTarget, Money);
	}
}
