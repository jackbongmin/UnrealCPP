// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponActor.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/ActionCharacter.h"
#include "Player/StatusComponent.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);

	WeaponMesh = CreateDefaultSubobject <USkeletalMeshComponent>(TEXT("Mesh"));
	WeaponMesh->SetupAttachment(root);
	WeaponMesh->SetCollisionProfileName(TEXT("NoCollision"));

	WeaponCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	WeaponCollision->SetupAttachment(WeaponMesh);
	WeaponCollision->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	//WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AWeaponActor::OnWeaponBeginOverlap);

}

void AWeaponActor::OnWeaponBeginOverlap(AActor* OverlapActor, AActor* OtherActor)
{
	float finalDamage = Damage;
	AController* instigator = nullptr;
	if (WeaponOwner.IsValid())
	{
		if (WeaponOwner == OtherActor)	// 내가 오버랩될 떄는 무시
			return;
		if (WeaponOwner->GetStatusComponent() != nullptr)	// 스테이터스 컴포넌트가 있으면 공격력 가져와서 추가하기
		{
			finalDamage += WeaponOwner->GetStatusComponent()->GetAttackPower();
		}
		instigator = WeaponOwner->GetController();
	}
	// UE_LOG(LogTemp, Log, TEXT("Overlapped : %s"), *OtherActor->GetName());
	UGameplayStatics::ApplyDamage(OtherActor, finalDamage, instigator, this, DamageType);
}

void AWeaponActor::AttackEnable(bool bEnable)
{
	//AActionCharacter* player = Cast<AActionCharacter>(WeaponOwner);

	if (bEnable)
	{
		//player->PlayAnimMontage(player->GetAttackMontage());
		WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AWeaponActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// CDO(Class Default Object)의 설정대로 초기화 된 이후( = OverlapOnlyPawn 설정 이후)
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called every frame
//void AWeaponActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

