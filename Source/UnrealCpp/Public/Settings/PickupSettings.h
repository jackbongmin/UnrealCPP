// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "PickupSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "All Pickup Settings"))
class UNREALCPP_API UPickupSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	

public:

	UPROPERTY(Config, EditAnywhere, Category = "Pickup Data")
	TSoftObjectPtr<UDataTable> PickupDataTable = nullptr;

};
