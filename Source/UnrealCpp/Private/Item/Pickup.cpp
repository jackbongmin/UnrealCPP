// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Pickup.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"
#include "NiagaraComponent.h"
#include "Player/InventoryOwner.h"



// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 루트  : 컬리전 추가(box)
	// 무기 외형 : 스켈레탈 메시
	// 오버랩 영역 : 스피어 컬리전
	// 이팩트 : 그대로

	BaseRoot = CreateDefaultSubobject<USphereComponent>(TEXT("Base"));
	SetRootComponent(BaseRoot);
	BaseRoot->InitSphereRadius(1.0f);
	BaseRoot->SetSimulatePhysics(true);
	BaseRoot->BodyInstance.bLockYRotation = true;
	BaseRoot->BodyInstance.bLockXRotation = true;
	BaseRoot->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(BaseRoot);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Mesh->AddRelativeRotation(FRotator(0, 0, -10.0f));

	PickupOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("Overlap"));
	PickupOverlap->SetupAttachment(BaseRoot);
	PickupOverlap->SetSphereRadius(200.0f);
	//PickupOverlap->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	PickupOverlap->SetCollisionProfileName(TEXT("NoCollision"));

	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	Effect->SetupAttachment(Mesh);

	PickupTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("PickupTimeline"));

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

	if (PickupTimeline)
	{
		if (ScaleCurve)
		{
			FOnTimelineFloat UpdateDelegate;
			UpdateDelegate.BindUFunction(this, FName("OnTimelineUpdate"));
			PickupTimeline->AddInterpFloat(DistanceCurve, UpdateDelegate);

			FOnTimelineEvent FinishDelegate;
			FinishDelegate.BindUFunction(this, FName("OnTimelineFinish"));
			PickupTimeline->SetTimelineFinishedFunc(FinishDelegate);
		}

		PickupTimeline->SetPlayRate(1/Duration);
	}

	FTimerManager& timerManager = GetWorldTimerManager();
	timerManager.ClearTimer(PickupableTimer);
	timerManager.SetTimer(
		PickupableTimer,
		[this]() {
			PickupOverlap->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
		},
		PickupableTime, false);

	bPickuped = false;
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Mesh->AddWorldRotation(FRotator(0, RotateSpeed* DeltaTime, 0));

}

void APickup::OnPickup_Implementation(AActor* Target)
{
	// 한번만 먹어지게
	if (!bPickuped)
	{
		// 먹기 처리
		UE_LOG(LogTemp, Log, TEXT("OnPickup_Implementation 실행"));
		bPickuped = true;

		PickupOwner = Target;
		BaseRoot->SetSimulatePhysics(false);	// 이 액터와 액터가 포함하는 모든 컴포넌트의 충돌 정지

		SetActorEnableCollision(false);			// 바닥으로 가라앉는것 방지

		FVector location = GetActorLocation();
		FVector location2 = Mesh->GetRelativeLocation();

		PickupStartLocation = Mesh->GetRelativeLocation() + GetActorLocation();	// Mesh의 월드 위치
		PickupTimeline->PlayFromStart();		// 타임라인 시작
	}
}

void APickup::OnPickupComplete_Implementation()
{
	Destroy();
}

void APickup::AddImpulse(FVector& Velocity)
{
	BaseRoot->AddImpulse(Velocity, NAME_None, true);
}

void APickup::OnTimelineUpdate(float Value)
{
	// 타임라인 정규화 된 진행 시간(0~1)
	float currentTime = PickupTimeline->GetPlaybackPosition();
	//UE_LOG(LogTemp, Log, TEXT("Timeline : %.2f"), currentTime);

	// 커브의 현재 값 받아오기
	float distanceValue = Value;
	float heightValue = HeightCurve ? HeightCurve->GetFloatValue(currentTime) : 0.0f;
	float scaleValue = ScaleCurve ? ScaleCurve->GetFloatValue(currentTime) : 1.0f;

	// 커브값을 기준으로 새위치와 스케일 계산
	FVector NewLocation = FMath::Lerp(PickupStartLocation, PickupOwner.Get()->GetActorLocation(), distanceValue);
	NewLocation += heightValue * PickupHeight * FVector::UpVector;
	Mesh->SetWorldLocation(NewLocation);
	//UE_LOG(LogTemp, Log, TEXT("NewLocation : %s"), *NewLocation.ToString());


	FVector NewScale = FVector::One() * scaleValue;
	Mesh->SetRelativeScale3D(NewScale);
}

void APickup::OnTimelineFinish()
{
	Execute_OnPickupComplete(this);


}

	