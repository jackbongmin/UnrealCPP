// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Inventory/InventoryWidget.h"
#include "MainHudWidget.generated.h"


UENUM(BlueprintType)
enum class EOpenState : uint8
{
	Open	UMETA(DisplayName = "Open"),
	Close	UMETA(DisplayName = "Close"),
};

/**
 * 
 */
UCLASS()
class UNREALCPP_API UMainHudWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:

	UFUNCTION(BlueprintCallable, Category = "UI|Inventory")
	void OpenInventory();
	
	UFUNCTION(BlueprintCallable, Category = "UI|Inventory")
	void CloseInventory();


	void AddToInventoryCloseDelegate(const FScriptDelegate& Delegate)
	{
		if (Inventory)
		{
			Inventory->OnInventoryCloseRequested.Add(Delegate);
		}
	}

	inline EOpenState GetOpenState() const { return OpenState; }
	inline UInventoryWidget* GetInventoryWidget() const { return Inventory; }

protected:
	// meta = (BindWidget)
	// 위젯 블루프린트의 변수와 이 클래스의 변수를 바인드 하겠다라는 의미(=둘이 같은거라고 설정)
	// 위젯 블루프린트의 변수명과 이 클래스의 변수명의 변수명이 반드시 같아야한다.(대소문자도 같아야함)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (BindWidget))
	TObjectPtr<class UResourceBarWidget> HealthBar = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resource", meta = (BindWidget))
	TObjectPtr<class UResourceBarWidget> StaminaBar = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (BindWidget))
	TObjectPtr<UInventoryWidget> Inventory = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop", meta = (BindWidget))
	TObjectPtr<class UShopWidget> Shop = nullptr;

private:
	EOpenState OpenState = EOpenState::Close;


};
