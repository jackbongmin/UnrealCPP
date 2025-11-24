// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UDamageWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetDamage(float Damage);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void PlayPopupAnimation();

protected:

	UPROPERTY(meta = (BindWidget))		// DamageText라는 애가 있을거야~ 라고 알려주는애
	TObjectPtr<class UTextBlock> DamageText = nullptr;

	UPROPERTY(Transient, meta = (BindWidgetAnim))	// Transient : 런타임에 임시로 생성된다고 명시, BindWidgetAnim : 애니메이션 바인딩
	TObjectPtr<UWidgetAnimation> PopupAnimation = nullptr;

};