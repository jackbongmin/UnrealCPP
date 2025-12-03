// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UsableItem.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUsableItem : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALCPP_API IUsableItem
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// InTarget 액터에게 이 아이템이 사용되었고 아이템의 데이터를 어떻게 사용해야 하는지 알려주는 용도
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ItemData|Usable")
	void UseItem(AActor* InTarget);


};
