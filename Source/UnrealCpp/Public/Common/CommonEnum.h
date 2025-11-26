// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EItemCode : uint8
{
	BasicFinger		UMETA(DisplayName = "기본손가락"),
	FireFinger		UMETA(DisplayName = "불손가락"),
	ThunderFinger	UMETA(DisplayName = "전기손가락"),
	IceFinger		UMETA(DisplayName = "얼음손가락"),
};

UENUM(BlueprintType)
enum class EWeaponCode : uint8
{
	BasicFinger		UMETA(DisplayName = "기본손가락"),
	FireFinger		UMETA(DisplayName = "불손가락"),
	ThunderFinger	UMETA(DisplayName = "전기손가락"),
	IceFinger		UMETA(DisplayName = "얼음손가락"),
};

// 비트플래그용 enum. 에디터에서 편집가능(블루프린트에서 변수를 만들었을 경우 int로 변수를 만들고 bitflag를 체크해줘야 한다)
UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EBitFlag : uint8
{
	None  = 0,
	Test1 = 1 << 0,
	Test2 = 1 << 1,
	Test3 = 1 << 2,
	Test4 = 1 << 3,
	Test5 = 1 << 4,
};

//// C++에서 Bitflag 변수 만들때
//UPROPERTY(EditAnywhere, meta = (Bitmast, BitmaskEnum = "EBitFlag"))
//int testBitFlag;

// 블루프린트에서 Bitflag 변수를 만들때
// int로 변수를 만들고 bitflag를 체크한 후 enum타입을 설정
