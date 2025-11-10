// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActionPlayerController.h"
#include "EnhancedInputSubSystems.h"
#include "InputMappingContext.h"

void AActionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, GameInputPriority);
	}
}
