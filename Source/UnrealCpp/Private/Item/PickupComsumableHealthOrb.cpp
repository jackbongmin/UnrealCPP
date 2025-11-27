// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickupComsumableHealthOrb.h"
#include "Player/HasHealth.h"

void APickupComsumableHealthOrb::OnConsume()
{
	Super::OnConsume();

	if (PickupOwner.IsValid())
	{
		if (PickupOwner.IsValid() && PickupOwner->Implements<UHasHealth>())
		{
			IHasHealth::Execute_HealHealth(PickupOwner.Get(), HealAmount);
		}

	}

}
