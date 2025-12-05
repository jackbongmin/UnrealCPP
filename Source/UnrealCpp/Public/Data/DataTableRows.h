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


USTRUCT(BlueprintType)
struct FShopData_TableRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	// 아이템 종류
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop")
	TObjectPtr<class UItemDataAsset> ItemData = nullptr;

	// 아이템이 상점에 등장할 가중치(1이 기본값, 숫자가 크면 클수록 잘나온다)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop", meta = (ClampMin = "0"))
	float SelectWeight = 1.0f;

	// 구매 가능한 아이템 갯수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop", meta = (ClampMin = "1"))
	int32 StockCount = 1;




};