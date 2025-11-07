// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));	// 씬 컴포넌트 하나 만들기
	SetRootComponent(root);															// 루트로 지정

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));		// 스테틱 메시 컴포넌트 하나 만들기
	BodyMesh->SetupAttachment(root);												// root 아래 붙히기
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
	BodyMesh->SetRelativeLocation(FVector(0, 0, 100));
}

void AFloatingActor::OnFloatingMeshUpdate(float DeltaTime)
{
	//교수님 cos풀이
	Deltatime1 += DeltaTime;

	float cosValue = FMath::Cos(Deltatime1);
	cosValue += 1;				// 2 -> 0 -> 2
	cosValue *= 0.5f;			// 1 -> 0 -> 1
	cosValue = 1 - cosValue;	// 0 -> 1 -> 0

	BodyMesh->SetRelativeLocation(FVector(0, 0, cosValue * MoveHeight));
	// z축으로 회전시키는거
	BodyMesh->AddRelativeRotation(FRotator(0, DeltaTime * SpinSpeed, 0));
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OnFloatingMeshUpdate(DeltaTime);
	
	//// 그냥 왔다갔다 하게하는거
	//BodyMesh->AddRelativeLocation(DeltaTime * Speed * FVector::UpVector);
	//FVector CurrentVector = BodyMesh->GetRelativeLocation();
	//
	//if (CurrentVector.Z > MoveHeight || CurrentVector.Z < 0)
	//{
	//	Speed *= -1;
	//}
	//
	//// cos를 이용해서 왔다갔다하게하는거
	//float Speed1 = 2.0f;

	//Deltatime1 += DeltaTime;

	//float cos11 = MoveHeight * (FMath::Cos(Deltatime1 * Speed1)+1);
	//UE_LOG(LogTemp, Log, TEXT("Cos:%f"),cos11);	// 로그 찍어서 값 확인

	//FVector CosLocation = BodyMesh->GetRelativeLocation();
	//CosLocation.Z = cos11;
	//BodyMesh->SetRelativeLocation(CosLocation);


	//// 교수님 풀이
	//if (BodyMesh->GetRelativeLocation().Z > MoveHeight || BodyMesh->GetRelativeLocation().Z < 0)
	//{
	//	Speed *= -1.0f;
	//}

}

