// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamagePopup1.generated.h"


/**
 * 
 */
UCLASS()
class UNREALCPP_API UDamagePopup1 : public UUserWidget
{
	GENERATED_BODY()
	
public:

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    UFUNCTION(BlueprintCallable)
    void SetDamage(float InDamage);

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* DamageText;

    void InitPopup(const FVector2D& StartPos);

private:
    float Lifetime = 1.0f;   
    float MoveSpeed = 40.0f;
    float Elapsed = 0.0f;
    FVector2D PositionOffset = FVector2D::ZeroVector;



};
