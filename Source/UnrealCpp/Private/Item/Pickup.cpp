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
	PickupOverlap->SetSphereRadius(100.0f);
	PickupOverlap->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	Effect->SetupAttachment(BaseRoot);

	PickupTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("PickupTimeline"));

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

	if (PickupOverlap)
	{
		PickupOverlap->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnPickupOverlap);
	}

	if (PickupTimeline)
	{
		if (ScaleCurve)
		{
			FOnTimelineFloat ScaleUpdateDelegate;
			ScaleUpdateDelegate.BindUFunction(this, FName("OnScaleUpdate"));
			PickupTimeline->AddInterpFloat(ScaleCurve, ScaleUpdateDelegate);

			FOnTimelineEvent ScaleFinishDelegate;
			ScaleFinishDelegate.BindUFunction(this, FName("OnScaleFinish"));
			PickupTimeline->SetTimelineFinishedFunc(ScaleFinishDelegate);
		}

		PickupTimeline->SetPlayRate(1/Duration);
	}
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
		bPickuped = true;
		PickupOwner = Target;
		//UE_LOG(LogTemp, Log, TEXT("OnPickup_Implementation 실행"));
		// 자신을 먹은 대상에게 자기를 가지고 있는 무기를 알려줘야 함
		StartLocation = GetActorLocation();
		TargetLocation = PickupOwner->GetActorLocation();
		SetActorEnableCollision(false);		// 이 액터와 액터가 포함하는 모든 컴포넌트의 충돌 정지
		PickupTimeline->PlayFromStart();	// 타임라인 시작
	}
}

void APickup::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Pickup Overlap"));
	//BaseRoot->SetSimulatePhysics(false);
	//BaseRoot->SetCollisionProfileName(TEXT("NoCollision"));
}

void APickup::OnScaleUpdate(float Value)
{
	FVector NewScale = FVector::One() * Value;
	SetActorScale3D(NewScale);

	if (PickupOwner.IsValid())
	{
		FVector PlayerLocation = PickupOwner->GetActorLocation();
		FVector Forward = PickupOwner->GetActorForwardVector();
		FVector DynamicTarget = PlayerLocation + Forward * 30.f;

		FVector Current = GetActorLocation();

		
		FVector NewLocation = FMath::VInterpTo(Current, DynamicTarget, GetWorld()->GetDeltaSeconds(), 10.0f);

		SetActorLocation(NewLocation);
	}
}

void APickup::OnScaleFinish()
{
	if (PickupOwner.IsValid() && PickupOwner->Implements<UInventoryOwner>())
	{
		IInventoryOwner::Execute_AddItem(PickupOwner.Get(), PickupItem);
	}
}

