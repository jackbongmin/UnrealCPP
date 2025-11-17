// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActionCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Player/ResourceComponent.h"
#include "Player/StatusComponent.h"
#include "Weapon/WeaponActor.h"
#include "Item/Pickupable.h"

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

	Resource = CreateDefaultSubobject<UResourceComponent>(TEXT("PlayerResource"));
	Status = CreateDefaultSubobject<UStatusComponent>(TEXT("PlayerStatus"));

	bUseControllerRotationYaw = false;							// 컨트롤러 yaw회전을 사용안함

	GetCharacterMovement()->bOrientRotationToMovement = true;	// 이동 방향을 바라보게 회전
	GetCharacterMovement()->RotationRate = FRotator(0, 360, 0);	// 1초에 360도 회전

}

// Called when the game starts or when spawned
void AActionCharacter::BeginPlay()
{
	if (Resource)
	{
		Resource->OnStaminaEmpty.AddDynamic(this, &AActionCharacter::SetWalkMode);
		if (Status)
		{
			Resource->SetMaxHealth(Status->GetMaxHealth());
			Resource->SetMaxStamina(Status->GetMaxStamina());

			//Resource->AddHealth(Status->GetMaxHealth());
			//Resource->AddStamina(Status->GetMaxStamina());
		}
	}
	Super::BeginPlay();	// 컴포넌트들의 BeginPlay가 실행된다.

	if (GetMesh())
	{
		AnimInstance = GetMesh()->GetAnimInstance();	// ABP 객체 가져오기
	}

	bIsSprinting = false;

	// 캐릭터에 다른 액터가 오버랩되었을 때 실행하기 위한 바인딩
	OnActorBeginOverlap.AddDynamic(this, &AActionCharacter::OnBeginOverlap);
}

// Called every frame	
void AActionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpendRunStamina(DeltaTime);
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
		enhanced->BindAction(IA_Attack, ETriggerEvent::Triggered, this, &AActionCharacter::OnAttackInput);
	}
}

void AActionCharacter::AddItem_Implementation(EItemCode Code)
{
	const UEnum* EnumPtr = StaticEnum <EItemCode>();
	UE_LOG(LogTemp, Log, TEXT("아이템 추가 : %s"), *EnumPtr->GetDisplayNameTextByValue(static_cast<int8>(Code)).ToString());
}

void AActionCharacter::OnAttackEnable(bool bEnable)
{
	if (CurrentWeapon.IsValid())
	{
		CurrentWeapon->AttackEnable(bEnable);
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
}

void AActionCharacter::OnRollInput(const FInputActionValue& InValue)
{
		if (AnimInstance.IsValid())
		{
			if (!AnimInstance->IsAnyMontagePlaying()
				&& Resource->HasEnoughStamina(RollStaminaCost))	// 몽타주 재생중이 아니고 충분한 스태미너가 있을 때만 작동
			{
				if (!GetLastMovementInputVector().IsNearlyZero())				// 입력을 하는 중에만 즉시 회전
					{
						SetActorRotation(GetLastMovementInputVector().Rotation());	// 마지막 입력 방향으로 즉시 회전시키기
					}
				Resource->AddStamina(-RollStaminaCost);	// 스테미너 감소
				PlayAnimMontage(RollMontage);
			}
		}
}

void AActionCharacter::OnAttackInput(const FInputActionValue& InValue)
{
	if (AnimInstance.IsValid() && Resource->HasEnoughStamina(AttackStaminaCost))	// 애님 인스턴스가 있고 스태미너도 충분할 때
	{
		if (!AnimInstance->IsAnyMontagePlaying())	// 몽타주 재생중이 아닐 때
		{
			// 첫번째 공격
			Resource->AddStamina(-AttackStaminaCost);	// 스테미너 감소
			PlayAnimMontage(AttackMontage);
		}
		else if (AnimInstance->GetCurrentActiveMontage() == AttackMontage)	// 몽타주가 재생 중인데, AttackMontage가 재생중이면
		{
			// 콤보 공격 시도
			SectionJumpForCombo();

		}
	}
}

void AActionCharacter::SetSprintMode()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	bIsSprinting = true;
}

void AActionCharacter::SetWalkMode()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	bIsSprinting = false;
}

void AActionCharacter::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Log, TEXT("Character overlap : other is %s"), *OtherActor->GetName());

	//// Cast를 이용한 인터페이스 사용
	//IPickupable* test = Cast<IPickupable>(OtherActor);
	//if (test)
	//{
	//	IPickupable::Execute_OnPickup(OtherActor);	// 만약에 블루프린트 구현이 있을 경우. 블루 프린트의 구현이 실행된다.
	//	//test->OnPickup_Implementation();			// 블루프린트 구현은 무시
	//}

	// Implements를 이용한 인터페이스 사용
	if (OtherActor->Implements<UPickupable>())		// OtherActor가 IPickable 인터페이스를 구현했는지 확인
	{
		IPickupable::Execute_OnPickup(OtherActor, this);	// 구현이 되어 있으면 실행
	}
}

void AActionCharacter::SectionJumpForCombo()
{
	if (SectionJumpNotify.IsValid() && bComboReady)	// SectionJumpNotify가 있고 콤보가 가능한 상태면
	{
		UAnimMontage* current = AnimInstance->GetCurrentActiveMontage();
		AnimInstance->Montage_SetNextSection(					// 다음 섹션으로 점프하기
			AnimInstance->Montage_GetCurrentSection(current),		// 현재 섹션
			SectionJumpNotify->GetNextSectionName(),				// 다음 섹션의 이름
			current);												// 실행될 몽타주

		bComboReady = false;		// 중복실행 방지
		Resource->AddStamina(-AttackStaminaCost);	// 스태미나 감소
	}
}

void AActionCharacter::SpendRunStamina(float DeltaTime)
{
	if ((bIsSprinting && !GetVelocity().IsNearlyZero())							// 달리기 상태이고 움직이지 않고 있다.
		&& (AnimInstance.IsValid() && !AnimInstance->IsAnyMontagePlaying()))	// 어떤 몽타주도 재생중이지 않다.(루트모션 때문에 velocity 변경 있음)
	{
		Resource->AddStamina(-SprintStaminaCost * DeltaTime);	// 스테미너 감소
	}
}
