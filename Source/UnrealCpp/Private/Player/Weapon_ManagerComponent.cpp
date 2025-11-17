// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Weapon_ManagerComponent.h"

// Sets default values for this component's properties
UWeapon_ManagerComponent::UWeapon_ManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeapon_ManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeapon_ManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

