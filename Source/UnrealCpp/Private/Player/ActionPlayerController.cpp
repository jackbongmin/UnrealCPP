// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActionPlayerController.h"
#include "EnhancedInputComponent.h"
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

	PlayerCameraManager->ViewPitchMax = ViewPitchMax;
	PlayerCameraManager->ViewPitchMin = ViewPitchMin;
}

void AActionPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* enhanced = Cast<UEnhancedInputComponent>(InputComponent);
	if (enhanced)	// 입력 컴포넌트가 향상된 입력 컴포넌트일 때
	{
		enhanced->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AActionPlayerController::OnLookInput);
	}

}

void AActionPlayerController::OnLookInput(const FInputActionValue& InValue)
{
	FVector2D lookAxis = InValue.Get<FVector2D>();
	AddYawInput(lookAxis.X);
	AddPitchInput(lookAxis.Y);
}
