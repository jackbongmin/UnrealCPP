// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	// Super = 부모클래스
	Super::BeginPlay();	// 부모 클래스의 BeginPlay를 실행해라.

	UE_LOG(LogTemp, Log, TEXT("Hello Unreal. ㅋㅋ 일반로그"));
	UE_LOG(LogTemp, Warning, TEXT("Hello Unreal. ㅋㅋ 경고로그"));
	UE_LOG(LogTemp, Error, TEXT("Hello Unreal. ㅋㅋ 에러로그"));

}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

