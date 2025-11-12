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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);	// 사망 알림용

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChanged, float, Current, float, Max);	// 스테미너 변경 알림용

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float);				// 체력 변경 알림용(비교를 위해 일반 델리게이트로 만듬)

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

	// 체력 추가/감소용 함수
	UFUNCTION(BlueprintCallable)
	void AddHealth(float InValue);

	// 생존 여부 확인용 함수
	UFUNCTION(BlueprintCallable, BlueprintPure)
	inline bool IsAlive() { return CurrentHealth > 0; }

	inline float GetCurrentHealth() const { return CurrentHealth; }
	inline float GetMaxHealth() const { return MaxHealth; }
	inline float GetCurrentStamina() const { return CurrentStamina; }
	inline float GetMaxStamina() const { return MaxStamina; }

	// 스태미너 추가/감소용 함수
	UFUNCTION(BlueprintCallable)
	void AddStamina(float InValue);

	// 스태미너가 충분한지 확인하는 함수
	UFUNCTION(BlueprintCallable, BlueprintPure)
	inline bool HasEnoughStamina(float InValue) { return CurrentStamina >= InValue; };

	// 스태미너가 다 떨어졌음을 알리는 델리게이트
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnStaminaEmpty OnStaminaEmpty;

	// 사망을 알리는 델리게이트
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnDie OnDie;

	// 스테미너 변화를 알리는 델리게이트
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnStaminaChanged OnStaminaChanged;

	// 체력변화를 알리는 델리게이트(일반 델리게이트는 블루프린트에서 사용 불능)
	FOnHealthChanged OnHealthChanged;

private:
	void StaminaAutoRegenCoolTimerSet();
	void StaminaRegenPerTick();

	inline void SetCurrentHealth(float InValue) {
		CurrentHealth = InValue;
		OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
	};
	inline void SetCurrentStamina(float InValue) {
		CurrentStamina = InValue;
		OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);
	};

	//inline void SetCurrentStamina(float InValue);

protected:

	// 현재 체력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Health")
	float CurrentHealth = 100.0f;

	// 최대 체력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Health")
	float MaxHealth = 100.0f;


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
