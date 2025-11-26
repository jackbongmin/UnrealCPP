// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Common/CommonStructures.h"
#include "EnemyPawn.generated.h"

UCLASS()
class UNREALCPP_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void TestDropItemCounts();

	UFUNCTION(BlueprintCallable)
	void TestDropItem(float BonusChange) { DropItem(BonusChange); };

private:
	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void DropItem(float BonusChange = 0.0f);

	void OnDie();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> PopupLocation = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Popup")
	TSubclassOf<class ADamagePopupActor> DamagePopupClass = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UResourceComponent> Resource = nullptr;

private:
	bool bInvincible = false;
	FTimerHandle InvincibleTimer;
	float LastDamage = 0.0f;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drop Items")
	TArray<FItemDropInfo> DropItemInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drop Items")
	TObjectPtr<class UDataTable> DropItemTable = nullptr;



};
