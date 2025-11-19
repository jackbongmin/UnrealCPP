// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Weapon_ManagerComponent.h"
#include "Weapon/WeaponActor.h"
#include "Weapon/UsedWeapon.h"
#include "Item/Pickup.h"
#include "Item/Consumable.h"

// Sets default values for this component's properties
UWeapon_ManagerComponent::UWeapon_ManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AWeaponActor* UWeapon_ManagerComponent::GetEquippedWeapon(EItemCode InType) const
{

	//if (const TObjectPtr<AWeaponActor>* weapon = WeaponInstance.Find(InType))
	//{
	//	return *weapon;
	//}

	AWeaponActor* weapon = nullptr;
	if (WeaponInstance.Contains(InType))
	{
		weapon = WeaponInstance[InType];
	}

	return weapon;

}

TSubclassOf<AUsedWeapon> UWeapon_ManagerComponent::GetUsedWeaponClass(EItemCode InType) const
{
	const UWeaponDataAsset* dataAsset = *WeaponDatabase.Find(InType);
	
	return dataAsset->UsedWeaponClass;
}

TSubclassOf<APickup> UWeapon_ManagerComponent::GetPickupWeaponClass(EItemCode InType) const
{

	const UWeaponDataAsset* dataAsset = *WeaponDatabase.Find(InType);
	
	return dataAsset->PickupWeaponClass;
}


// Called when the game starts
void UWeapon_ManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPlayer = Cast<AActionCharacter>(GetOwner());

	ValidateWeaponDatabase();
	SpawnWeaponInstance();

	//WeaponInstance[EItemCode::BasicFinger];
	//AWeaponActor* basicWeapon = GetEquippedWeapon(EItemCode::BasicFinger);
	//basicWeapon->WeaponActivate(true);
	OwnerPlayer->EquipWeapon(EItemCode::BasicFinger);	// 시작 무기
}

void UWeapon_ManagerComponent::ValidateWeaponDatabase()
{
	if (WeaponDatabase.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("무기 데이터베이스가 비었음!"));
	}
	else
	{
		for (const auto& pair : WeaponDatabase)	// 이거 뭔지 질문
		{
			if (!pair.Value)
			{
				UE_LOG(LogTemp, Error, TEXT("무기(%d)의 데이터가 null"), static_cast<int32>(pair.Key));
			}
			else if (!pair.Value->IsValid())
			{
				UE_LOG(LogTemp, Error, TEXT("무기(%d)의 유효하지 않습니다."), static_cast<int32>(pair.Key));
			}
			else if (pair.Key != pair.Value->WeaponType)
			{
				UE_LOG(LogTemp, Warning, TEXT("무기(%d)의 키값과 데이터 타입이 서로 다릅니다."), static_cast<int32>(pair.Key));
			}
		}
	}
}

void UWeapon_ManagerComponent::SpawnWeaponInstance()
{
	WeaponInstance.Empty(WeaponDatabase.Num());		// WeaponInstance의 할당 크기를 필요한만큼만 할당

	if (OwnerPlayer.IsValid())
	{
		UWorld* world = GetWorld();
		FVector defaultLocation = FVector(0, 0, -10000.0f);
		for (const auto& pair : WeaponDatabase)
		{
			AWeaponActor* weapon = world->SpawnActor<AWeaponActor>(
				pair.Value->EquippedWeaponClass,
				defaultLocation,
				FRotator::ZeroRotator);				// 일단 defaultLocation 위치에 생성
			weapon->AttachToComponent(
				OwnerPlayer->GetMesh(),
				FAttachmentTransformRules::KeepWorldTransform,
				FName("root"));							// 월드아웃라이너에서 확인하기 위해 플레이어 아래에 붙임
			weapon->SetWeaponOwner(OwnerPlayer.Get());	// 무기의 오너 설정
			weapon->WeaponActivate(false);				// 무기 비활성화



			WeaponInstance.Add(pair.Key, weapon);		// 인스턴스 맵에 추가
		}

	}


	
}




