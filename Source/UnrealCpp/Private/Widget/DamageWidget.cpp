// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DamageWidget.h"
#include "Components/TextBlock.h"


void UDamageWidget::SetDamage(float Damage)
{
	if (DamageText)
	{
		DamageText->SetText(FText::AsNumber(static_cast<int32>(Damage)));
	}
}

void UDamageWidget::PlayPopupAnimation()
{
	if(PopupAnimation)
	{
		PlayAnimation(PopupAnimation, 0, 1, EUMGSequencePlayMode::Forward, 1.0f);
	}
}
