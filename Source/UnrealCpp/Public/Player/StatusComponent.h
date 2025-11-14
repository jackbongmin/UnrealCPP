// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCPP_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();


public:	
	// 스테이터스와 모디파이어를 기반으로 공격력 계산해서 리턴하는 함수
	float GetAttackPower();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Status")
	float GetHealthBonus() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Status")
	float GetStaminaBonus() const;

protected:
	// 힘 스탯
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (ClampMin = "0", ClampMax = "20"))
	int32 Strength = 10;
	
	// 민첩 스탯
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (ClampMin = "0", ClampMax = "20"))
	int32 Agility = 10;
	
	// 생명력 스탯
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (ClampMin = "0", ClampMax = "20"))
	int32 Vitality = 10;

	// 공격력 모디파이어
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifiers")
	float AttackModifier = 1.0f;

		
};
