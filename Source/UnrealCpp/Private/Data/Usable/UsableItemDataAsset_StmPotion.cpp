// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Usable/UsableItemDataAsset_StmPotion.h"
#include "Player/HasStamina.h"



void UUsableItemDataAsset_StmPotion::UseItem_Implementation(AActor* InTarget)
{
	if (InTarget->Implements<UHasStamina>())
	{
		IHasStamina::Execute_RecoveryStamina(InTarget, RecoveryAmount);
	}
}
