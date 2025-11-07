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

protected:
	int32 Data1 = 10;

	UPROPERTY(VisibleAnywhere, Category = "Test 변수")		// 클래스 디폴트나 인스턴스에서 보기 가능
	int32 Data2 = 20;

	UPROPERTY(VisibleDefaultsOnly, Category = "Test 변수")	// 클래스 디폴트 창에서만 보기 가능
	int32 Data3 = 30;

	UPROPERTY(VisibleInstanceOnly, Category = "Test 변수")	// 맵에 배치된 상태에서만 디테일창으로 보기가능
	int32 Data4 = 40;

	UPROPERTY(EditAnyWhere, Category = "Test 변수")			// 클래스 디폴트나 인스턴스에서 편집 가능
	int32 Data5 = 50;
	
	UPROPERTY(EditDefaultsOnly, Category = "Test 변수")		// 클래스 디폴트 창에서만 편집 가능
	int32 Data6 = 60;
	
	UPROPERTY(EditInstanceOnly, Category = "Test 변수")		// 맵에 배치된 상태에서만 디테일창에서 편집가능
	int32 Data7 = 70;

	UPROPERTY(BlueprintReadOnly, Category = "Test 변수")		// 블루프린트 쪽에서 읽기만 가능
	int32 Data8 = 80;

	UPROPERTY(BlueprintReadWrite, Category = "Test 변수")	// 블루프린트쪽에서 읽고 쓰기 가능
	int32 Data9 = 90;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Test 변수")		// 확인은 어디서든 할 수 있고 블루프린트에서 읽고 쓰기 가능
	int32 Data10 = 100;
};
