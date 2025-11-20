// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/NiagaraTest.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANiagaraTest::ANiagaraTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	Effect->SetupAttachment(Root);
	Effect->SetRelativeLocation(FVector(0, 0, 100));
	Effect->SetAutoActivate(false);

	Overlap = CreateDefaultSubobject<USphereComponent>(TEXT("Overlap"));
	Overlap->SetupAttachment(Root);
	Overlap->SetSphereRadius(100.f);
	Overlap->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//Overlap->SetCollisionResponseToAllChannels(ECR_Overlap);
	Overlap->OnComponentBeginOverlap.AddDynamic(this, &ANiagaraTest::OnOverlapBegin);
	Overlap->OnComponentEndOverlap.AddDynamic(this, &ANiagaraTest::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ANiagaraTest::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANiagaraTest::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Entered!"));

		// Niagara 켜기
		ActivateNiagaraEffect(true);

		// 데미지 주기
		UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, nullptr, this, nullptr);

		bIsPlayerInside = true;
	}
}

void ANiagaraTest::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Left!"));

		// Niagara 끄기
		ActivateNiagaraEffect(false);

		bIsPlayerInside = false;
	}
}

// Called every frame
void ANiagaraTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANiagaraTest::TestColorChange(const FLinearColor& Incolor)
{
	Effect->SetColorParameter(TEXT("EffectColor"), Incolor);
	//Effect->SetNiagaraVariableLinearColor(TEXT("EffectColor"), Incolor);
}

void ANiagaraTest::ActivateNiagaraEffect(bool bActivate)
{
	if (!Effect) return;

	if (bActivate)
		Effect->Activate(true);
	else
		Effect->Deactivate();
}

