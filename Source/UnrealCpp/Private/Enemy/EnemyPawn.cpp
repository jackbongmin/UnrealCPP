// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPawn.h"
#include "Enemy/DamagePopupActor.h"
#include "Framework/DamagePopupSubSystem.h"
#include "Framework/EnemyTrackingSubsystem.h"
#include "Framework/PickupFactorySubsystem.h"
#include "Player/ResourceComponent.h"
#include "Data/DataTableRows.h"
#include "Item/Pickup.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	PopupLocation = CreateDefaultSubobject<USceneComponent>(TEXT("PopupLocation"));
	PopupLocation->SetupAttachment(Mesh);
	PopupLocation->SetRelativeLocation(FVector(0, 0, 100));

	Resource = CreateDefaultSubobject<UResourceComponent>(TEXT("Resource"));

}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &AEnemyPawn::OnTakeDamage);

	if (UWorld* world = GetWorld())
	{
		if (UEnemyTrackingSubsystem* enemyTracker = world->GetSubsystem<UEnemyTrackingSubsystem>())
		{
			enemyTracker->RegistEnemy();
		}
	}
}

void AEnemyPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UWorld* world = GetWorld())
	{
		if (UEnemyTrackingSubsystem* enemyTracker = world->GetSubsystem<UEnemyTrackingSubsystem>())
		{
			enemyTracker->UnregistEnemy();
		}
	}
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyPawn::TestDropItemCounts()
{
	APickup* pickup = nullptr;
	TMap<FName, uint8*> RowMap = DropItemTable->GetRowMap();
	TArray<int32> counter = { 0,0,0 };
	//counter.Empty(3);

	for (int i = 0; i < 1000000; i++)
	{
		if (DropItemTable)
		{
			int index = 0;
			// 아이템 중복으로 당첨 가능
			for (const auto& element : RowMap)
			{
				pickup = nullptr;
				FDropItemData_v2_TableRows* row = (FDropItemData_v2_TableRows*)element.Value;
				if (FMath::FRand() <= row->DropRate)
				{

					counter[index]++;
				}

				index++;
			}
		}
	}
	UE_LOG(LogTemp, Log, TEXT("Test count : 100만"));
	UE_LOG(LogTemp, Log, TEXT("index 0 : %d"), counter[0]);
	UE_LOG(LogTemp, Log, TEXT("index 0 : %d"), counter[1]);
	UE_LOG(LogTemp, Log, TEXT("index 0 : %d"), counter[2]);
}

void AEnemyPawn::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Log, TEXT("Damage : %.1f"), Damage);
	if (Resource->IsAlive())
	{

		if (!bInvincible || !FMath::IsNearlyEqual(LastDamage, Damage))
		{
			Resource->AddHealth(-Damage);
			//ADamagePopupActor* actor = GetWorld()->SpawnActor<ADamagePopupActor>(
			//	DamagePopupClass, PopupLocation->GetComponentToWorld());
			//if (actor)
			//{
			//	actor->PopupActivate(Damage);
			//}

			UDamagePopupSubSystem* popupSystem = GetWorld()->GetSubsystem<UDamagePopupSubSystem>();
			popupSystem->ShowDamagePopup(Damage, PopupLocation->GetComponentLocation());

			if (Resource->IsAlive())
			{
				bInvincible = true;
				LastDamage = Damage;

				FTimerDelegate resetDelegate = FTimerDelegate::CreateWeakLambda(
					this,
					[this]()
					{
						bInvincible = false;
					});	// this가 파괴되면 람다는 더 이상 실행되지 않는다.

				GetWorldTimerManager().ClearTimer(InvincibleTimer);
				GetWorldTimerManager().SetTimer(
					InvincibleTimer,
					[this]() {
						bInvincible = false;
					},
					0.1f, false);
			}
			else
			{
				OnDie();
			}

		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("이 적은 이미 죽었다."));
	}

}

void AEnemyPawn::DropItem(float BonusChange)
{
	//for (auto item : DropItemInfo)
	//{
	//	item.DropRate;
	//	item.DropItemClass;
	//}

	if (DropItemTable)
	{
		//TArray<FDropItemData_TableRow*
		//DropItemTable->GetAllRows<FDropItemData_TableRow>(TEXT("Rows"), AllRows);

		APickup* pickup = nullptr;
		TMap<FName, uint8*> RowMap = DropItemTable->GetRowMap();
		
		// 아이템 중복으로 당첨 가능
		for (auto& element : RowMap)
		{
			pickup = nullptr;
			FDropItemData_v2_TableRows* row = (FDropItemData_v2_TableRows*)element.Value;
			
			if (FMath::FRand() - BonusChange <= row->DropRate)
			{
				//pickup = GetWorld()->SpawnActor<APickup>(
				//	row->DropItemClass,
				//	GetActorLocation() + FVector::UpVector * 200.0f,
				//	GetActorRotation());

				pickup = GetWorld()->GetSubsystem<UPickupFactorySubsystem>()->SpawnPickup(
					row->PickupCode,
					PopupLocation->GetComponentLocation(),
					GetActorRotation());

				FVector LaunchVelocity = FVector::UpVector * 500.0f;
				LaunchVelocity = LaunchVelocity.RotateAngleAxis(FMath::FRandRange(-15.0f, 15.0f), FVector::RightVector);
				LaunchVelocity = LaunchVelocity.RotateAngleAxis(FMath::FRandRange(0.0f, 360.0f), FVector::UpVector);
				DrawDebugLine(
					GetWorld(),
					PopupLocation->GetComponentLocation(),
					PopupLocation->GetComponentLocation() + LaunchVelocity,
					FColor::Green, false, 3.0f
				);
				pickup->AddImpulse(LaunchVelocity);

			}

			if (pickup)
			{
				UE_LOG(LogTemp, Log, TEXT("Drop Success : %s"), *pickup->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("Drop empty"));
			}
		}

		//// 전체 가중치 사용하는 방식(한개만 뽑기)
		//float totalWeight = 0.0f;
		//for (const auto& element : RowMap)
		//{
		//	FDropItemData_TableRow* row = (FDropItemData_TableRow*)element.Value;
		//	totalWeight += row->DropRate;

		//}
		//float randomSelect = FMath::FRandRange(0, totalWeight);
		//float currentWeight = 0.0f;
		//for (const auto& element : RowMap)
		//{
		//	FDropItemData_TableRow* row = (FDropItemData_TableRow*)element.Value;
		//	currentWeight += row->DropRate;
		//	if (randomSelect < currentWeight)
		//	{
		//		pickup = GetWorld()->SpawnActor<APickup>(
		//			row->DropItemClass,
		//			GetActorLocation() + FVector::UpVector * 200.0f,
		//			GetActorRotation());
		//		break;
		//	}
		//}

	}
}

void AEnemyPawn::OnDie()
{
	DropItem();
	Destroy();	// 죽었으면 삭제
}

