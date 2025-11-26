// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Common/CommonEnum.h"
#include "DataTableRows.generated.h"


/**
 * 
 */

USTRUCT(BlueprintType)
struct FDropItemData_v1_TableRows : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class APickup> DropItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", ClampMax = "1"))
	float DropRate = 1.0f;

};

USTRUCT(BlueprintType)
struct FDropItemData_v2_TableRows : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItemCode PickupCode = EItemCode::BasicFinger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", ClampMax = "1"))
	float DropRate = 1.0f;

};

USTRUCT(BlueprintType)
struct FPickDataTableRows : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	EItemCode PickupCode = EItemCode::BasicFinger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	TSubclassOf<class APickup> PickupClass = nullptr;

};
