// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "ActionPlayerController.generated.h"

class UInputMappingContext;	// UInputMappingContext라는 클래스가 있다고 알려주는 역할
class UInputAction;
/**
 * 
 */
UCLASS()
class UNREALCPP_API AActionPlayerController : public APlayerController
{
	GENERATED_BODY()

	//UInputMappingContext a;	// 안됨) 전방 선언한 것은 헤더가 없으면 인스턴스를 만들 수 없다.
	//UInputMappingContext* b;	// 됨)   전방 선언한 것의 주소는 저장할 수 있다.(모든 타입의 주소 크기는 같으니까)
public:
	virtual void SetupInputComponent() override;

private:
	void OnLookInput(const FInputActionValue& InValue);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Look;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|Pitch")
	float ViewPitchMin = -40;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|Pitch")
	float ViewPitchMax = 30;


private:
	int32 GameInputPriority = 1;
	
};
