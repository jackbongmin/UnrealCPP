// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Common/CommonEnum.h"
#include "ItemDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UNREALCPP_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
	// FString(법용), FName(내부코드용), FText(외부용, 로컬라이제이션용)

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemData")
	EItemCode ItemCode = EItemCode::Figure;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemData")
	FText ItemName = FText::FromString(TEXT("아이템"));
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemData")
	FText ItemDescription = FText::FromString(TEXT("아이템 설명"));
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemData")
	UTexture2D* ItemIcon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemData", meta = (ClampMin = "1"))
	int32 ItemPrice = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemData", meta = (ClampMin = "1"))
	int32 ItemMaxStackCount = 1;



};
