// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));	// 씬 컴포넌트 하나 만들기
	SetRootComponent(root);															// 루트로 지정

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));		// 스테틱 메시 컴포넌트 하나 만들기
	BodyMesh->SetupAttachment(root);												// root 아래 붙히기
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
	BodyMesh->SetRelativeLocation(FVector(0, 0, 100));
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	BodyMesh->AddRelativeLocation(DeltaTime * Speed * FVector::UpVector);
}

