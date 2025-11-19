// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ConsumableWeapon.h"

void AConsumableWeapon::OnAttack()
{
	RemaingUseCount--;
	if (RemaingUseCount <= 0)
	{
		OnWeaponUseEnded.Broadcast(WeaponID);
	}
}

void AConsumableWeapon::OnWeaponPickuped(int InCount)
{
	// 현재 사용되는 곳 없음
	Super::OnWeaponPickuped(InCount);

	RemaingUseCount = InCount;

}

void AConsumableWeapon::BeginPlay()
{
	Super::BeginPlay();
	RemaingUseCount = MaxUseCount;
}

void AConsumableWeapon::OnWeaponActivate()
{
	RemaingUseCount = MaxUseCount;
}