// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyState_Last1.h"
#include "Player/ActionCharacter.h"

void UAnimNotifyState_Last1::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!OwnerCharacter.IsValid())
	{
		OwnerCharacter = Cast<AActionCharacter>(MeshComp->GetOwner());
	}

	if (OwnerCharacter.IsValid())
	{
		OwnerCharacter->OnLastAttackEnable(true);
		OwnerCharacter->OnLastEffectAttackEnable(true);
	}
}

void UAnimNotifyState_Last1::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{

	if (OwnerCharacter.IsValid())
	{
		OwnerCharacter->OnLastAttackEnable(false);
		OwnerCharacter->OnLastEffectAttackEnable(false);
	}
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
