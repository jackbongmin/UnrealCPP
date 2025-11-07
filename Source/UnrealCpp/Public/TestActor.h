// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//generated.h는 모든 헤더 중 마지막에 있어야 한다.
#include "TestActor.generated.h"

UCLASS()
class UNREALCPP_API ATestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Test_NormalFuction();

	// BlueprintCallable : C++로 작성한 함수를 블루프린트에서 호출할 수 있다.
	UFUNCTION(BlueprintCallable, Category = "내 함수")	

	void Test_UFunction();

	// BlueprintImplementableEvent : C++에서 선언만 하고 구현은 블루프린트에서 할 경우
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "내 함수")	
	void Test_ImplementableFunction();
	
	// BlueprintNativeEvent
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "내 함수")
	void Test_NativeEventFunction();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
