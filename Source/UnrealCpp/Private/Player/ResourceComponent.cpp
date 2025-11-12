// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ResourceComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UResourceComponent::UResourceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UResourceComponent::BeginPlay()
{
	Super::BeginPlay();

	// 게임 진행 중에 자주 변경되는 값은 시작 지점에서 리셋을 해주는 것이 좋다.
	CurrentStamina = MaxStamina;	// 시작할때 최대치로 리셋

	// ...
	
}


// Called every frame
void UResourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	//// 타이머로 조건만 설정하는 경우
	//if(bRegenStamina)
	//{
	//	CurrentStamina += StaminaRegenAmount * DeltaTime;
	//	if (CurrentStamina > MaxStamina)
	//	{
	//		bRegenStamina = false;
	//		CurrentStamina = MaxStamina;
	//	}
	//}
}

void UResourceComponent::AddStamina(float InValue)
{
	// 스태미너 변경 처리
	CurrentStamina += InValue;

	//TimeSinceLastStaminaUse = 0.0f;	// 시간을 직접 제어할 때 쓰던 코드

	// 스테미너를 소비하고 일정 시간 뒤에 자동재생되게 타이머 세팅
	StaminaAutoRegenCoolTimerSet();

	if (CurrentStamina <= 0)
	{
		CurrentStamina = 0.0f;
		// 델리게이트(디스패처)로 스테미너가 떨어졌음을 알림
		OnStaminaEmpty.Broadcast();
	}
	StaminaUpdate.Broadcast();
}


void UResourceComponent::StaminaAutoRegenCoolTimerSet()
{
	UWorld* world = GetWorld();
	FTimerManager& timerManager = world->GetTimerManager();	// 이 두줄이 아래랑 똑같은 내용임
	//GetWorldTimerManager().ClearTimer(StaminaCoolTimer);		// 해서 나쁠 것은 없음(SetTimer 할 때 이미 내부적으로 처리하고 있다.)

	timerManager.SetTimer(
		StaminaAutoRegenCoolTimer,
		[this]() {
			//bRegenStamina = true;
			UWorld* world = GetWorld();
			FTimerManager& timerManager = world->GetTimerManager();
			timerManager.SetTimer(
				StaminaRegenTickTimer,
				this,
				&UResourceComponent::StaminaRegenPerTick,
				StaminaTickInterval,	// 실행 간격
				true,	// 반복 재생 여부
				StaminaTickInterval);	// 첫 딜레이
		},
		StaminaRegenCoolTime,
		false);
	StaminaUpdate.Broadcast();
}

void UResourceComponent::StaminaRegenPerTick()
{
	CurrentStamina += StaminaRegenAmountPerTick;	// 틱당 최대 스테미너의 10%
	//CurrentStamina += MaxStamina * StaminaRegenAmountRatePerTick;	// 틱당 최대 스테미너의 10%

	if (CurrentStamina > MaxStamina)
	{
		CurrentStamina = MaxStamina;
		UWorld* world = GetWorld();
		FTimerManager& timerManager = world->GetTimerManager();
		timerManager.ClearTimer(StaminaRegenTickTimer);
	}
	StaminaUpdate.Broadcast();
}

