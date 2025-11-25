// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/EnemyTrackingSubsystem.h"


void UEnemyTrackingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentEnemyCount = 0;	// 혹시나 싶어서 넣은 코드(없어도 상관없음)
}

void UEnemyTrackingSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UEnemyTrackingSubsystem::RegistEnemy()
{
	CurrentEnemyCount++;
	OnEnemyCountChanged.Broadcast(CurrentEnemyCount);
}

void UEnemyTrackingSubsystem::UnregistEnemy()
{
	if (CurrentEnemyCount > 0)
	{
		CurrentEnemyCount--;
		OnEnemyCountChanged.Broadcast(CurrentEnemyCount);

		if (CurrentEnemyCount <= 0)
		{
			OnAllEnemyClear.Broadcast();
		}
	}
}