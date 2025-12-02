// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/ActionPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"
#include "InputMappingContext.h"
#include "Framework/MainHUD.h"
#include "Player/InventoryComponent.h"
#include "Player/ActionCharacter.h"


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

void AActionPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	AActionCharacter* player = Cast<AActionCharacter>(aPawn);
	if (player)
	{
		InventoryComponent = player->GetInventoryComponent();
		if (InventoryWidget.IsValid())
		{
			InventoryWidget->InitializeInventoryWidget(InventoryComponent.Get());
		}
	}
}

void AActionPlayerController::OnUnPossess()
{
	if(InventoryWidget.IsValid())
	{
		InventoryWidget->ClearInventoryWidget();
	}
	InventoryComponent = nullptr;
	Super::OnUnPossess();
}

void AActionPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* enhanced = Cast<UEnhancedInputComponent>(InputComponent);
	if (enhanced)	// 입력 컴포넌트가 향상된 입력 컴포넌트일 때
	{
		enhanced->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AActionPlayerController::OnLookInput);
		enhanced->BindAction(IA_InventoryOnOff, ETriggerEvent::Started, this, &AActionPlayerController::OnInventoryOnOff);
	}
}

void AActionPlayerController::OnLookInput(const FInputActionValue& InValue)
{
	FVector2D lookAxis = InValue.Get<FVector2D>();
	AddYawInput(lookAxis.X);
	AddPitchInput(lookAxis.Y);
}

void AActionPlayerController::OnInventoryOnOff()
{
	if (MainHudWidget.IsValid())
	{
		if (MainHudWidget->GetOpenState() == EOpenState::Open)
		{
			CloseInventoryWidget();
		}
		else
		{
			OpenInventoryWidget();
		}
	}
}

void AActionPlayerController::OpenInventoryWidget()
{
	if (MainHudWidget.IsValid())
	{
		MainHudWidget->OpenInventory();

		//FInputModeGameOnly;	: 게임 전용(입력이 플레이어 컨트롤러로 우선 전달됨, 마우스 커서가 안보임)
		//FInputModeUIOnly;		: UI가 떠있을때 사용(입력이 UI로 먼저 전달됨, 마우스 커서가 보임)
		//FInputModeGameAndUI;	: 마우스를 클릭했을 때 UI가 아래에 있으면 ui로 처리하고, 없으면 game으로 처리

		FInputModeGameAndUI inputMode;
		inputMode.SetWidgetToFocus(MainHudWidget->TakeWidget());				// 위젯에 포커스 주기
		inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);	// 마우스 커서가 뷰포트를 벗어날 수 있게 설정
		inputMode.SetHideCursorDuringCapture(false);							// 마우스가 눌려졌을 때도 커서가 보이도록 설정
		SetInputMode(inputMode);												// InputMode를 플레이어 컨트롤러에 적용

		bShowMouseCursor = true;

		SetIgnoreMoveInput(true);	// 이동 입력 무시
		SetIgnoreLookInput(true);	// 카메라 회전 입력 무시

		//SetPause(true);				// 게임 일시정지
	}
}

void AActionPlayerController::CloseInventoryWidget()
{
	if (MainHudWidget.IsValid())
	{
		//SetPause(false);				// 게임 일시정지

		SetIgnoreMoveInput(false);	// 이동 입력 다시 받기
		SetIgnoreLookInput(false);	// 카메라 회전 입력 다시 받기

		FInputModeGameOnly inputMode;
		SetInputMode(inputMode);

		bShowMouseCursor = false;

		MainHudWidget->CloseInventory();
	}
}

void AActionPlayerController::InitializeMainHudWidget(UMainHudWidget* InWidget)
{
	if (InWidget)
	{
		MainHudWidget = InWidget;

		// MainHudWidget의 Inventory의 닫힘 델리게이트에 함수 연결
		FScriptDelegate delegate;
		delegate.BindUFunction(this, "CloseInventoryWidget");
		MainHudWidget->AddToInventoryCloseDelegate(delegate);

		InventoryWidget = MainHudWidget->GetInventoryWidget();
		if(InventoryWidget.IsValid())	// Possess보다 타이밍이 늦다.
		{
			InventoryWidget->InitializeInventoryWidget(InventoryComponent.Get());
		}
	}
}

void AActionPlayerController::TestChangeInventoryTarget(UInventoryComponent* NewTarget)
{
	if (NewTarget)
	{
		InventoryWidget->InitializeInventoryWidget(NewTarget);
	}
}
