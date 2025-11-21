// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyState_WeaponTrail.h"
#include "Player/ActionCharacter.h"

void UAnimNotifyState_WeaponTrail::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (!OwnerCharacter.IsValid())
	{
		OwnerCharacter = Cast<AActionCharacter>(MeshComp->GetOwner());
	}
	if (OwnerCharacter.IsValid())
	{
		// 무기 이펙트 켜기
		OwnerCharacter->OnWeaponTrailEnable(true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UAnimNotufyState_WeaponTrail::NotifyBegin : OwnerCharacter가 유효하지 않습니다."));
	}
}

void UAnimNotifyState_WeaponTrail::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (OwnerCharacter.IsValid())
	{
		//무기 이펙트 끄기
		OwnerCharacter->OnWeaponTrailEnable(false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UAnimNotufyState_WeaponTrail::NotifyEnd : OwnerCharacter가 유효하지 않습니다."));
	}
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
