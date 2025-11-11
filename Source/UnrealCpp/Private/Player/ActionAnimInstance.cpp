// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActionAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"	// UPawnMovementComponent 이거때매

void UActionAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* ownerPawn = TryGetPawnOwner();
	if (ownerPawn)
	{
		OwnerMovementComponent = ownerPawn->GetMovementComponent();
	}
}

void UActionAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//TryGetPawnOwner()->GetVelocity().Size();	// Tick이나 Update같이 빠르게 반복되는 곳에서는 불필요한 중복 실행은 방지 해야한다.

	if (OwnerMovementComponent.IsValid())
	{
		//const UPawnMovementComponent* movement = OwnerMovementComponent.Get();
		//Speed = movement->Velocity.Size();

		Speed = OwnerMovementComponent.Get()->Velocity.Size();	// 위에꺼랑 같은것

	}
}
