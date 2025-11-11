// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActionCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AActionCharacter::AActionCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 350.0f;
	SpringArm->SocketOffset = FVector(0, 0, 250);
	SpringArm->bUsePawnControlRotation = true;					// 스프링암의 회전을 컨트롤러에 맞춤

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(SpringArm);
	PlayerCamera->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));

	bUseControllerRotationYaw = false;							// 컨트롤러 yaw회전을 사용안함

	GetCharacterMovement()->bOrientRotationToMovement = true;	// 이동 방향을 바라보게 회전
	GetCharacterMovement()->RotationRate = FRotator(0, 360, 0);	// 1초에 360도 회전

}

// Called when the game starts or when spawned
void AActionCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AActionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhanced = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (enhanced)	// 입력 컴포넌트가 향상된 입력 컴포넌트일 때
	{
		enhanced->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AActionCharacter::OnMoveInput);
		enhanced->BindActionValueLambda(IA_Sprint, ETriggerEvent::Started,
			[this](const FInputActionValue& _) {
				SetSprintMode();
			});
		enhanced->BindActionValueLambda(IA_Sprint, ETriggerEvent::Completed,
			[this](const FInputActionValue& _) {
				SetWalkMode();
			});
	}
}

void AActionCharacter::OnMoveInput(const FInputActionValue& InValue)
{
	// 카메라 방향이 캐릭터 움직임을 따라가지 않을때
	
	FVector2D inputDirection = InValue.Get<FVector2D>();
	//UE_LOG(LogTemp, Log, TEXT("Dir : (%.1f, %.1f)"), inputDirection.X, inputDirection.Y);
	//UE_LOG(LogTemp, Log, TEXT("Dir : (%s)"), *inputDirection.ToString());
	
	FVector moveDirection(inputDirection.Y, inputDirection.X, 0.0f);
	
	FQuat controlYawRotation = FQuat(FRotator(0, GetControlRotation().Yaw, 0));
	moveDirection = controlYawRotation.RotateVector(moveDirection);
	
	AddMovementInput(moveDirection);

	//// 카메라 방향이 캐릭터 움직임을 따라갈때(내가한거)

	//FVector2D Input = InValue.Get<FVector2D>();

	//// 현재 카메라(컨트롤러)의 회전값
	//FRotator ControlRot = GetControlRotation();
	//ControlRot.Pitch = 0.0f; // 상하 각도는 이동에 필요 없어서 0으로
	//ControlRot.Roll = 0.0f;

	//// 방향 벡터 계산
	//const FVector Forward = FRotationMatrix(ControlRot).GetUnitAxis(EAxis::X);
	//const FVector Right = FRotationMatrix(ControlRot).GetUnitAxis(EAxis::Y);
	//
	//// 입력값 기반으로 이동 입력
	//AddMovementInput(Forward, Input.Y);
	//AddMovementInput(Right, Input.X);
}

void AActionCharacter::SetSprintMode()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AActionCharacter::SetWalkMode()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}


