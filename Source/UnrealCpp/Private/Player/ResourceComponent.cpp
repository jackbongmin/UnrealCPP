// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ResourceComponent.h"
#include "GameFramework/Actor.h"
#include "Player/StatusComponent.h"

// Sets default values for this component's properties
UResourceComponent::UResourceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	
}


// Called when the game starts
void UResourceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	if (AActor* Owner = GetOwner())
	{
		if (UStatusComponent* StatusComp = Owner->FindComponentByClass<UStatusComponent>())
		{
			
			MaxHealth = MaxHealth + StatusComp->GetHealthBonus();
			MaxStamina = MaxStamina + StatusComp->GetStaminaBonus();

			CurrentHealth = MaxHealth;
			CurrentStamina = MaxStamina;
		}
	}
	// 게임 진행 중에 자주 변경되는 값은 시작 지점에서 리셋을 해주는 것이 좋다.
	SetCurrentHealth(MaxHealth);
	SetCurrentStamina(MaxStamina);	// 시작할때 최대치로 리셋

}


// Called every frame
//void UResourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//
//	//// 타이머로 조건만 설정하는 경우
//	//if(bRegenStamina)
//	//{
//	//	CurrentStamina += StaminaRegenAmount * DeltaTime;
//	//	if (CurrentStamina > MaxStamina)
//	//	{
//	//		bRegenStamina = false;
//	//		CurrentStamina = MaxStamina;
//	//	}
//	//}
//}

void UResourceComponent::AddHealth(float InValue)
{
	float health = CurrentHealth + InValue;

	SetCurrentHealth(FMath::Clamp(health, 0.0f, MaxHealth));

	CurrentHealth += InValue;
	if (!IsAlive())
	{
		OnDie.Broadcast();
	}
}

void UResourceComponent::AddStamina(float InValue)
{
	// 스태미너 변경 처리
	CurrentStamina += InValue;

	//TimeSinceLastStaminaUse = 0.0f;	// 시간을 직접 제어할 때 쓰던 코드

	if (InValue < 0)
	{
		// 스테미너를 소비하고 일정 시간 뒤에 자동재생되게 타이머 세팅
		StaminaAutoRegenCoolTimerSet();
	}

	SetCurrentStamina(FMath::Clamp(CurrentStamina, 0, MaxStamina));
	if (CurrentStamina <= 0)
	{
		// 델리게이트(디스패처)로 스테미너가 떨어졌음을 알림
		OnStaminaEmpty.Broadcast();
	}

}


void UResourceComponent::StaminaAutoRegenCoolTimerSet()
{
	UWorld* world = GetWorld();
	FTimerManager& timerManager = world->GetTimerManager();		// 이 두줄이 아래랑 똑같은 내용임
	//GetWorldTimerManager().ClearTimer(StaminaCoolTimer);		// 해서 나쁠 것은 없음(SetTimer 할 때 이미 내부적으로 처리하고 있다.)

	timerManager.ClearTimer(StaminaRegenTickTimer);				// 스테미나 회복중에 스태미나 소모시 회복 중지
	timerManager.SetTimer(
		StaminaAutoRegenCoolTimer,	// 3초기다리게함	// StaminaAutoRegenCoolTimer 핸들에 연결될 타이머 세팅.(StaminaAutoRegenCoolTimer초 후에 한번만 람다식을 실행하는 타이머)
		[this]() {
			//bRegenStamina = true;
				// StaminaAutoRegenCoolTimer핸들에 연결될 타이머 세팅
				//		StaminaTickInterval초를 처음에 한번 기다리고, 
				//		StaminaTickInterval시간 간격으로 
				//		이 클래스의 StaminaRegenPerTick함수를 실행하는 타이머
			UWorld* world = GetWorld();
			FTimerManager& timerManager = world->GetTimerManager();
			timerManager.SetTimer(
				StaminaRegenTickTimer,	// 지속적으로 회복하게함
				this,
				&UResourceComponent::StaminaRegenPerTick,
				StaminaTickInterval,	// 실행 간격
				true,					// 반복 재생 여부
				StaminaTickInterval);	// 첫 딜레이
		},
		StaminaRegenCoolTime,
		false);
}

void UResourceComponent::StaminaRegenPerTick()
{
	float stamina = CurrentStamina + StaminaRegenAmountPerTick;
		// 틱당 최대 스테미너의 10%
	//CurrentStamina += MaxStamina * StaminaRegenAmountRatePerTick;	// 틱당 최대 스테미너의 10%

	if (stamina > MaxStamina)
	{
		stamina = MaxStamina;
		UWorld* world = GetWorld();
		FTimerManager& timerManager = world->GetTimerManager();
		timerManager.ClearTimer(StaminaRegenTickTimer);
	}

	SetCurrentStamina(stamina);
}

