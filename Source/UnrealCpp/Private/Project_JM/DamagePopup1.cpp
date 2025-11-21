// Fill out your copyright notice in the Description page of Project Settings.


#include "Project_JM/DamagePopup1.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetLayoutLibrary.h"


void UDamagePopup1::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    Elapsed += InDeltaTime;

    PositionOffset.Y -= MoveSpeed * InDeltaTime;

    float Alpha = 1.0f - (Elapsed / Lifetime);
    if (DamageText)
    {
        DamageText->SetRenderOpacity(Alpha);
    }

    SetRenderTranslation(PositionOffset);

    // 다 사라지면 제거
    if (Elapsed >= Lifetime)
    {
        RemoveFromParent();
    }
}

void UDamagePopup1::SetDamage(float InDamage)
{
    if (DamageText)
    {
       DamageText->SetText(FText::AsNumber(FMath::RoundToInt(InDamage)));
    }
}

void UDamagePopup1::InitPopup(const FVector2D& StartPos)
{
    SetPositionInViewport(StartPos, true);

    PositionOffset = FVector2D::ZeroVector; 
}
