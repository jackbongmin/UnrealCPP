// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Usable/UsableItemDataAsset_HealthPotion.h"
#include "Player/HasHealth.h"



void UUsableItemDataAsset_HealthPotion::UseItem_Implementation(AActor* InTarget)
{
	if (InTarget->Implements<UHasHealth>())
	{
		IHasHealth::Execute_HealHealth(InTarget, HealAmount);
	}
}
