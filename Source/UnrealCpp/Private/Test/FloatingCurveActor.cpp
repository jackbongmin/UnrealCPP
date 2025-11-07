// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/FloatingCurveActor.h"

void AFloatingCurveActor::OnFloatingMeshUpdate(float DeltaTime)
{
	if (HeightCurve)
	{
		// 커브가 있음
		Deltatime1 += DeltaTime;

		float curveInput = FMath::Fmod(Deltatime1 / Duration, 1.0f);	// Duration을 이용해서 한주기 시간 결정, 0.0 ~ 1.0 범위의 숫자로 반복
		float curveValue = HeightCurve->GetFloatValue(curveInput);		// 0 ~ 1 ~ 0
		
		UE_LOG(LogTemp, Log, TEXT("%f"), MoveHeight);

		BodyMesh->SetRelativeLocation(FVector(0, 0, curveValue * MoveHeight));
		BodyMesh->AddRelativeRotation(FRotator(0, SpinSpeed * DeltaTime, 0));
	}
	else
	{
		// 커브가 없음
		Super::OnFloatingMeshUpdate(DeltaTime);
	}
}
