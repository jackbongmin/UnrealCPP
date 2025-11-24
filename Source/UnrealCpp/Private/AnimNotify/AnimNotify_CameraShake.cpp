// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotify_CameraShake.h"

void UAnimNotify_CameraShake::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!CameraManager.IsValid())	// CameraManager가 없으면 미리 찾아 놓기
	{
		UWorld* world = MeshComp->GetWorld();
		if (world)
		{
			CameraManager = world->GetFirstPlayerController()->PlayerCameraManager;
		}
	}

	if (CameraShake && CameraManager.IsValid())	// class랑 매니저 둘다 있을 때만 실행
	{
		CameraManager->StartCameraShake(CameraShake);
	}

}
