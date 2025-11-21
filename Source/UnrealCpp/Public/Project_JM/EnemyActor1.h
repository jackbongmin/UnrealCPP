// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor1.generated.h"

class UDamagePopup1;

UCLASS()
class UNREALCPP_API AEnemyActor1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void SpawnDamagePopup(float Damage);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Project_JM|state")
	float CurrentHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Project_JM|state")
	float MaxHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Project_JM|Components")
	TObjectPtr<UStaticMeshComponent> MainMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Project_JM|Components")
	TObjectPtr<UStaticMeshComponent> SubMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Project_JM|Components")
	class UCapsuleComponent* HitCollision;

	UPROPERTY(EditAnywhere, Category = "Project_JM|UI")
	TSubclassOf<class UUserWidget> DamagePopupClass;

};
