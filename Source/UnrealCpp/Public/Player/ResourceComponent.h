// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourceComponent.generated.h"


// DELEGATE
// 그냥 Delegate vs DynamicDelegate
//  - DynamicDelegate는 블루프린트에서 사용가능
//  - DynamicDelegate는 일반 Delegate에 비해 느리다.
//  - DynamicDelegate에는 람다식 추가가 불가능하다.
//  - DynamicDelegate에 바인딩 되는 함수는 UFUNCTION으로 선언되어야 한다.
// 그냥 Delegate vs MulicastDelegate
//  - MulicastDelegate는 여러 리스너를 바인딩 할 수 있다.
// Dlegate vs Event
//  - Event는 외부에서 바인딩만 가능
//  - Delegate는 외부에서 바인딩과 실행 모두 가능
// 선언은 클래스 외부에서 선언

// 선언은 서로 조합이 가능함
// DECLARE_DELEGATE
// DECLARE_DYNAMIC_DELEGATE
// DECLARE_MULTICAST_DELEGATE
// DECLARE_MULTICAST_DELEGATE
// DECLARE_DYNAMIC_MULTICAST_DELEGATE
// DECLARE_DELEGATE_Retval
// DECLARE_DELEGATE_Retval_OneParam

// FOnStaminaEmpty 이름의 델리게이트가 있다라고 타입을 선언한것
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaEmpty);

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCPP_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResourceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 스태미너 추가/감소용 함수
	UFUNCTION(BlueprintCallable)
	void AddStamina(float InValue);

	// 스태미너가 충분한지 확인하는 함수
	UFUNCTION(BlueprintCallable, BlueprintPure)
	inline bool HasEnoughStamina(float InValue) { return CurrentStamina >= InValue; };

	// 스태미너가 다 떨어졌음을 알리는 델리게이트
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnStaminaEmpty  OnStaminaEmpty;

private:
	void StaminaAutoRegenCoolTimerSet();
	void StaminaRegenPerTick();

protected:

	// 현재 스테미나
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Stamina")
	float CurrentStamina = 100.0f;

	// 최대 스테미나
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Stamina")
	float MaxStamina = 100.0f;
		
	// 스테미너가 자동 회복되는데 걸리는 시간
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Stamina")
	float StaminaRegenCoolTime = 3.0f;

	// 스태미너 틱 간격
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Stamina")
	float StaminaTickInterval = 0.1f;

	// 스테미나 자동 회복량(틱당)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Stamina")
	float StaminaRegenAmountPerTick = 10.0f;

	// 스테미나 자동 회복량(틱당, 최대치의 %)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Stamina")
	float StaminaRegenAmountRatePerTick = 0.1f;

private:

	//float TimeSinceLastStaminaUse = 0.0f;
	//bool bRegenStamina = false;

	FTimerHandle StaminaAutoRegenCoolTimer;	// 스태미너가 자동 회복용 타이머 핸들
	FTimerHandle StaminaRegenTickTimer;		// 스태미너 자동 회복시 틱별 타이머 핸들

};
