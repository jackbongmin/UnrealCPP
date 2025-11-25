// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonStructures.generated.h"

USTRUCT(BlueprintType)
struct FTestStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 DataA = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DataB = 15.5;
};


USTRUCT(BlueprintType)
struct FItemDropInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drop Items Info")
	TSubclassOf<class APickup> DropItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drop Items Info")
	float DropRate;
};

