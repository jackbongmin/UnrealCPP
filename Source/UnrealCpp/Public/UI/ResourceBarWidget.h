// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResourceBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UResourceBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RefreshWidget(float InCurrent, float InMax);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual void NativePreConstruct() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (BindWidget))	// meta = (BindWidget) 이거는 위젯에서 변수여부 체크해서 활용할때 무조건 써야 하는 애
	TWeakObjectPtr<class UProgressBar> Bar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (BindWidget))
	TWeakObjectPtr<class UTextBlock> Current;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (BindWidget))
	TWeakObjectPtr<class UTextBlock> Max;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Color")
	FLinearColor FillColor = FLinearColor::Yellow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Color")
	FLinearColor BackgroundColor = FLinearColor(0.0f, 1.0f, 0.0f, 0.2f);
	

};
