// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "EnemyTrackingSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyCountChanged, int32, NewCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllEnemyClear);
/**
 * 
 */
UCLASS()
class UNREALCPP_API UEnemyTrackingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Enemy Tracker")
	int32 GetCurrentEnemyCount() const { return CurrentEnemyCount; }

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void RegistEnemy();
	void UnregistEnemy();
	
public:

	// 적 수가 변경되었을 때 실행될 델리게이트
	UPROPERTY(BlueprintAssignable, Category = "EnemyTracker")
	FOnEnemyCountChanged OnEnemyCountChanged;

	// 적이 모두 사라졌을 때 실행될 델리게이트
	UPROPERTY(BlueprintAssignable, Category = "EnemyTracker")
	FOnAllEnemyClear OnAllEnemyClear;


private:

	int32 CurrentEnemyCount = 0;

};
