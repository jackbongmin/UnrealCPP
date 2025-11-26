// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/PickupFactorySubsystem.h"
#include "Settings/PickupSettings.h"
#include "Data/DataTableRows.h"


void UPickupFactorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LoadPickupClassesMap();
}

APickup* UPickupFactorySubsystem::SpawnPickup(EItemCode InCode, FVector InLocation, FRotator InRotator)
{
	APickup* spawnedPickup = nullptr;
	if (PickupClasses.Contains(InCode))
	{
		UWorld* world = GetWorld();
		spawnedPickup = world->SpawnActor<APickup>(PickupClasses[InCode], InLocation, InRotator);

	}
	else
	{

	}
	return spawnedPickup;
}

void UPickupFactorySubsystem::LoadPickupClassesMap()
{
	const UPickupSettings* settings = GetDefault<UPickupSettings>();
	if (settings && !settings->PickupDataTable.IsNull())
	{
		UDataTable* dataTable = settings->PickupDataTable.LoadSynchronous();
		if (dataTable)
		{
			TArray<FPickDataTableRows*> allRows;
			dataTable->GetAllRows(TEXT("PickupDataTable"), allRows);
			for (const FPickDataTableRows* row : allRows)
			{
				if (PickupClasses.Contains(row->PickupCode))
				{

				}
				PickupClasses.Add(row->PickupCode, row->PickupClass);
			}
		}
		else
		{

		}
	}
	else
	{

	}
}
