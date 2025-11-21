// Fill out your copyright notice in the Description page of Project Settings.


#include "Project_JM/EnemyActor1.h"
#include "Project_JM/DamagePopup1.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyActor1::AEnemyActor1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    HitCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitCollision"));
    SetRootComponent(HitCollision);
    HitCollision->SetCollisionProfileName(TEXT("Pawn"));
    HitCollision->SetGenerateOverlapEvents(true);

    MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
    MainMesh->SetupAttachment(HitCollision);
    MainMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    SubMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SubMesh"));
    SubMesh->SetupAttachment(MainMesh);
    SubMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AEnemyActor1::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHP = MaxHP;
}

// Called every frame
void AEnemyActor1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AEnemyActor1::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	CurrentHP -= DamageAmount;

	SpawnDamagePopup(DamageAmount);
    UE_LOG(LogTemp, Warning, TEXT("Enemy Hit! Damage: %f"), DamageAmount);
	return DamageAmount;
}

void AEnemyActor1::SpawnDamagePopup(float Damage)
{
    //UE_LOG(LogTemp, Warning, TEXT("SpawnDamagePopup Called!"));
    //UE_LOG(LogTemp, Warning, TEXT("PopupClass: %s"),
    //    *DamagePopupClass->GetName());

    if (!DamagePopupClass) return;

    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    FVector HeadPos = GetActorLocation() + FVector(0, 0, 120);
    FVector2D ScreenPos;
    PC->ProjectWorldLocationToScreen(HeadPos, ScreenPos);

    UDamagePopup1* Popup = CreateWidget<UDamagePopup1>(GetWorld(), DamagePopupClass);
    if (Popup)
    {
        Popup->AddToViewport(1000);

        Popup->InitPopup(ScreenPos);

        Popup->SetDamage(Damage);
    }
}

