// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Enemy/DamagePopupActor.h"
#include "DamagePopupSettings.generated.h"


/**
 * 
 */

// Config = Game : 설정의 Game 카테고리에 저장(Config/DefaultGame.ini)
// DefaultConfig : 이 클래스 값이 기본 설정(프로젝트 원본 = Config 폴더에 있는 ini에 저장된다.)
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Damage Popup Settings"))
class UNREALCPP_API UDamagePopupSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	// Config : 이 PROPERTY는 ini파일에 저장되고 불러와질 수 있다.
	// TSoftClassPtr : 소프트 레퍼런스라 필요한 시점에 연결된 리소스를 로딩할 수 있다.
	// 하드 래퍼런스 : 하드 래퍼런스를 가지고 있는 오브젝트를 로딩하면 하드 레퍼런스에 있는 리소스도 동시에 로딩된다.
	UPROPERTY(Config, EditAnywhere, Category = "UI")
	TSoftClassPtr<ADamagePopupActor> DamagePopupClass = nullptr;
};
