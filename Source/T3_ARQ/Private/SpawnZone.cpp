// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnZone.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"




// Sets default values
ASpawnZone::ASpawnZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	VisualBox = CreateDefaultSubobject<UBoxComponent>(TEXT("VisualBox"));
	RootComponent = VisualBox;
	VisualBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	VisualBox->SetHiddenInGame(true); // Solo visible en el editor

}

// Called when the game starts or when spawned
void ASpawnZone::BeginPlay()
{
	Super::BeginPlay();
	SpawnRandomActors();

}

void ASpawnZone::SpawnRandomActors()
{
	UWorld* World = GetWorld();
	if (!World) return;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FHitResult Hit;


	if (!BP_Class) return;
	FVector Origin = GetActorLocation();
	FVector Extent = VisualBox->GetScaledBoxExtent(); // ya considera escala

	for (int32 i = 0; i < SpawnCount; ++i)
	{
		// Generar punto aleatorio en X/Y dentro de la caja
		float RandX = FMath::FRandRange(-Extent.X, Extent.X);
		float RandY = FMath::FRandRange(-Extent.Y, Extent.Y);
		FVector StartLocation = Origin + FVector(RandX, RandY, TraceZStart);
		FVector EndLocation = Origin + FVector(RandX, RandY, TraceZEnd);

		bool bHit = World->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility, Params);

		if (bHit)
		{
			FVector SpawnLocation = Hit.ImpactPoint + FVector(0, 0, 50); // evitar clipping

			FString Msg = FString::Printf(TEXT("Impact Z: %.2f"), Hit.ImpactPoint.Z);
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Msg);

			World->SpawnActor<AActor>(BP_Class, SpawnLocation, FRotator::ZeroRotator);


		}
	}

}



// Called every frame
void ASpawnZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

