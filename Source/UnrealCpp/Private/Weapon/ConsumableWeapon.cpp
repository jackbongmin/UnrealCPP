// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ConsumableWeapon.h"

void AConsumableWeapon::OnAttack()
{
	RemaingUseCount--;
	if (RemaingUseCount <= 0)
	{
		OnWeaponUseEnded.Broadcast();
	}
}

void AConsumableWeapon::OnWeaponPickuped(AActionCharacter* InOwner)
{
	Super::OnWeaponPickuped(InOwner);

	RemaingUseCount = MaxUseCount;

}
