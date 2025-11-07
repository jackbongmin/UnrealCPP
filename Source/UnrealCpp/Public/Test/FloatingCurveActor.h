// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Test/FloatingActor.h"
#include "FloatingCurveActor.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPP_API AFloatingCurveActor : public AFloatingActor
{
	GENERATED_BODY()

protected:
	virtual void OnFloatingMeshUpdate(float DeltaTime) override;
	
public :
	// 높이를 움직임을 결정할 커브
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UCurveFloat> HeightCurve = nullptr;

	// 커브 한주기 동안의 시간
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Duration = 5.0f;
};
