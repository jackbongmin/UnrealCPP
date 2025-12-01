// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MainHUD.h"
#include "Blueprint/UserWidget.h"
#include "Player/ActionPlayerController.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainWidgetClass)
	{
		MainWidgetInstance = CreateWidget<UMainHudWidget>(GetWorld(), MainWidgetClass);
		if (MainWidgetInstance)
		{
			MainWidgetInstance->AddToViewport();

			// HUD는 플레이어 컨트롤러가 있어야 만들어지기 때문에 이 타이밍에는 둘 다 있음이 보장된다.
			AActionPlayerController* pc = Cast<AActionPlayerController>(GetOwningPlayerController());
			if (pc)
			{
				pc->InitializeMainHudWidget(MainWidgetInstance);
			}
		}
	}
}
