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

	AnimInstance = GetMesh()->GetAnimInstance();	// ABP 객체 가져오기
	
}

// Called every frame
void AActionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsSprinting)
	{
		Stamina -= 1.0f * DeltaTime;

		if (Stamina <= 0.0f)
		{
			Stamina = 0.0f;
			SetWalkMode();  
		}
	}

	if (!bIsSprinting && !AnimInstance->IsAnyMontagePlaying())
	{
		StaminaTimer += DeltaTime;
		if (StaminaTimer > 3.0f)
		{
			bRecoverStamina = true;
			Stamina += 2.0f * DeltaTime;
			Stamina = FMath::Clamp(Stamina, 0.0f, 10.0f);
		}
		
	}
	UE_LOG(LogTemp, Log, TEXT("Stamina : (%.1f)"), Stamina);

	
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
		enhanced->BindAction(IA_Roll, ETriggerEvent::Triggered, this, &AActionCharacter::OnRollInput);
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

void AActionCharacter::OnRollInput(const FInputActionValue& InValue)
{
	if (Stamina > 0.0f)
	{
		if (AnimInstance.IsValid())
		{
			if (!AnimInstance->IsAnyMontagePlaying())
			{
				if (!GetLastMovementInputVector().IsNearlyZero())				// 입력을 하는 중에만 즉시 회전
					{
						SetActorRotation(GetLastMovementInputVector().Rotation());	// 마지막 입력 방향으로 즉시 회전시키기
					}
				PlayAnimMontage(RollMontage);
				Stamina -= 5.0f;
				StaminaTimer = 0.0f;
				Stamina = FMath::Clamp(Stamina, 0.0f, 10.0f);
			}
		}
	}
}

void AActionCharacter::SetSprintMode()
{
	if (Stamina > 0.0f)
	{
		bIsSprinting = true;
		StaminaTimer = 0.0f;
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void AActionCharacter::SetWalkMode()
{
	
	bIsSprinting = false;
	StaminaTimer = 0.0f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	
}


