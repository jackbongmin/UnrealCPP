// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ActionAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API UActionAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed = 0.0f;
	
private:
	TWeakObjectPtr<const UPawnMovementComponent> OwnerMovementComponent = nullptr;
};
