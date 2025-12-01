// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/MainHudWidget.h"
#include "MainHUD.generated.h"


/**
 * 
 */
UCLASS()
class UNREALCPP_API AMainHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	inline UMainHudWidget* GetMainWidget() const { return MainWidgetInstance; }

protected:
	// MainWidgetClass는 UMainHudWidget의 파생 클래스 타입만 가능(객체가 아니라 타입을 저장한다)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UMainHudWidget> MainWidgetClass = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UMainHudWidget> MainWidgetInstance = nullptr;

};
