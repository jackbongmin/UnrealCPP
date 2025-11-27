// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickupComsumable.h"

void APickupComsumable::OnPickupComplete_Implementation()
{
	OnConsume();	// 기능 동작

	Super::OnPickupComplete_Implementation();	// 자기 자신 삭제
}

void APickupComsumable::OnConsume()
{
	if (DataAsset)
	{
		DataAsset->Excute(PickupOwner.Get());
	}
}