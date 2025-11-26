// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "AnimNotify/AnimNotifyState_SectionJump.h"
#include "InventoryOwner.h"
#include "ActionCharacter.generated.h"	// 얘는 항상 마지막 헤더에 들어가있어야함

class UInputAction;
class USpringArmComponent;
class UResourceComponent;
class UStatusComponent;
//class UAnimNotifyState_SectionJump;

UCLASS()
class UNREALCPP_API AActionCharacter : public ACharacter, public IInventoryOwner
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AActionCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 아이템 추가 인터페이스 함수 구현
	void AddItem_Implementation(EItemCode Code, int32 Count);

	// 무기를 장비하는 함수
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EquipWeapon(EWeaponCode WeaponCode);

	// 노티파이가 무기의 트레일을 표시하라고 신호가 왔을 때 실행될 함수
	void OnWeaponTrailEnable(bool bEnable);

	// 노티파이가 범위 공격을 하라고 신호가 왔을 때 실행될 함수
	void OnAreaAttack();

	// 노티파이가 공격을 가능하게 만들라는 신호가 왔을 때 실행될 함수
	void OnAttackEnable(bool bEnable);


	UResourceComponent* GetResourceComponent() { return Resource; }
	UStatusComponent* GetStatusComponent() { return Status; }


	inline void SetSectionJumpNotify(UAnimNotifyState_SectionJump* InSectionJumpNotify)
	{
		SectionJumpNotify = InSectionJumpNotify; 
		bComboReady = InSectionJumpNotify != nullptr;
	}



	// 테스트용 함수
	UFUNCTION(BlueprintCallable)
	void TestDropUsedWeapon();

	UFUNCTION(BlueprintCallable)
	void TestCurrentWeapon();
	

protected:
	// 이동 방향 입력 받기
	void OnMoveInput(const FInputActionValue& InValue);
	
	// 구르기 입력 받기
	void OnRollInput(const FInputActionValue& InValue);
	
	// 공격 입력 받기
	void OnAttackInput(const FInputActionValue& InValue);

	// 달리기 모드 설정
	void SetSprintMode();
	// 걷기 모드 설정(다이나믹 델리게이트에 바인드하기위해 UFUNCTION 추가)
	UFUNCTION()
	void SetWalkMode();

	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	//UFUNCTION(BlueprintCallable, Category = "Player")
	//void OnWeaponUseEnded();

private:
	
	UFUNCTION()
	void OnAttackMonTageEnded(UAnimMontage* Montage, bool bInsterrupted);

	// 콤보용 섹션 점프 함수
	void SectionJumpForCombo();
	
	// 달리기용 스태미너 소비 함수
	void SpendRunStamina(float DeltaTime);

	//// 사용 다한 무기를 던지는 함수
	//void DropUsedWeapon();

		// 다쓴 무기를 버리는 함수
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void DropWeapon(EWeaponCode WeaponCode);


	// 사용 중이던 무기를 버리는 함수
	void DropCurrentWeapon(EWeaponCode WeaponCode);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera")
	TObjectPtr <USpringArmComponent> SpringArm = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera")
	TObjectPtr<class UCameraComponent> PlayerCamera = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Resource")
	TObjectPtr<class UResourceComponent> Resource = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Status")
	TObjectPtr<class UStatusComponent> Status = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Weapon")
	TObjectPtr<USceneComponent> DropLocation = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Weapon")
	TObjectPtr<class UWeapon_ManagerComponent> WeaponManager = nullptr;

	// 인풋 엑션들
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Move = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Sprint = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Roll = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Attack = nullptr;

protected:
	// 달리기 속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Movement")
	float SprintSpeed = 1200.0f;

	// 걷기 속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Movement")
	float WalkSpeed = 600.0f;

	

	//달리기 상태일 때 초당 스테미너 비용
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Resource")
	float SprintStaminaCost = 20.0f;

	// 구르기를 하기위해 필요한 스테미너 비용
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Resource")
	float RollStaminaCost = 50.0f;

	// 공격 하기위해 필요한 스테미너 비용
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Resource")
	float AttackStaminaCost = 15.0f;
	

	// 플레이어가 뛰고 있는 중인지 표시 해놓은 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player|State")
	bool bIsSprinting = false;

	//// 사용 다한 무기 액터(순수 장식)
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Weapon")
	//TMap<EItemCode, TSubclassOf<class AUsedWeapon>> UsedWeapons;
	//
	//// pickup할 수 있는 무기 엑터
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Weapon")
	//TMap<EItemCode, TSubclassOf<class APickup>> PickupWeapons;

	// 구르기 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage")
	TObjectPtr<UAnimMontage> RollMontage = nullptr;

	// 공격 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Montage")
	TObjectPtr<UAnimMontage> AttackMontage = nullptr;

	// 플레이어가 현재 가지고 있는 무기
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player|Weapon")
	TWeakObjectPtr<class AWeaponActor> CurrentWeapon = nullptr;



private:
	UPROPERTY()
	TWeakObjectPtr<UAnimInstance> AnimInstance = nullptr;	// AnimInstance => ABP에 대한 포인터	/ TObjectPtr, TWeakObjectPtr 차이는 중요도? 라고 보면 될거같음. T옵젝은 반드시 가져야 할때, T윅옵젝은 참조가 버려져도 될때

	// 현재 진행중인 섹션점프 노티파이 스테이트
	UPROPERTY()
	TWeakObjectPtr<UAnimNotifyState_SectionJump> SectionJumpNotify = nullptr;

	// 콤보가 가능한 상황인지 확인하기 위한 플래그
	bool bComboReady = false;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Weapon", meta = (AllowPrivateAccess = "true"))
	//bool bWeaponUseEnded = false;

};
