// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Consumable/HealthOrbDataAsset.h"
#include "Player/HasHealth.h"

void UHealthOrbDataAsset::Excute(AActor* InTarget) const
{
	if (InTarget && InTarget->Implements<UHasHealth>())
	{
		IHasHealth::Execute_HealHealth(InTarget, HealAmount);
	}

}
