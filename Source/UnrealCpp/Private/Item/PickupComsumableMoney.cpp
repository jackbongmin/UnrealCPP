// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickupComsumableMoney.h"
#include "Player/InventoryOwner.h"


void APickupComsumableMoney::OnConsume()
{
	Super::OnConsume();

	if (PickupOwner.IsValid())
	{
		if (PickupOwner.IsValid() && PickupOwner->Implements<UInventoryOwner>())
		{
			IInventoryOwner::Execute_AddMoney(PickupOwner.Get(), Money);
		}

	}
}
