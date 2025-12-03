// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TemporarySlot.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UTemporarySlot : public UUserWidget
{
	GENERATED_BODY()
	

public:
	void SetItemIconImage(UTexture2D* InTexture);
	void SetCountText(int32 InCount);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|IventorySlot", meta = (BindWidget))
	TObjectPtr<class UImage> ItemIconImage = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|IventorySlot", meta = (BindWidget))
	TObjectPtr<class UTextBlock> CountText = nullptr;


};
