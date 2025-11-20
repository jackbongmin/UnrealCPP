// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/NiagaraTest.h"
#include "NiagaraComponent.h"

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
}

// Called when the game starts or when spawned
void ANiagaraTest::BeginPlay()
{
	Super::BeginPlay();
	
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

