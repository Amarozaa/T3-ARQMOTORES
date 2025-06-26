// Fill out your copyright notice in the Description page of Project Settings.

#include "lootChest.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"

// Sets default values
AlootChest::AlootChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	RootComponent = Base;

	Tapa = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tapa"));
	Tapa->SetupAttachment(Base);

	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
	TriggerSphere->InitSphereRadius(100.0f);
	TriggerSphere->SetupAttachment(RootComponent);
	TriggerSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerSphere->SetCollisionObjectType(ECC_WorldDynamic);
	TriggerSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

// Called when the game starts or when spawned
void AlootChest::BeginPlay()
{
	Super::BeginPlay();

	InitialRotation = Tapa->GetRelativeRotation();
	TargetRotation = InitialRotation + FRotator(-anguloApertura, 0.0f, 0.0f);
	CurrentLerpAlpha = 0.0f;
	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AlootChest::OnOverlapBegin);
	TriggerSphere->OnComponentEndOverlap.AddDynamic(this, &AlootChest::OnOverlapEnd);
}

// Called every frame
void AlootChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsOpen && CurrentLerpAlpha < 1.0f)
	{
		CurrentLerpAlpha += DeltaTime / velocidadApertura;

		Tapa->SetRelativeRotation(FMath::Lerp(InitialRotation, TargetRotation, CurrentLerpAlpha));
	}
}

void AlootChest::Interact()
{
	if (!IsOpen)
	{
		IsOpen = true;
		SpawnLoot();
	}
}

void AlootChest::SpawnLoot()
{
	if (ItemPool.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, ItemPool.Num() - 1);
		TSubclassOf<AActor> ItemToSpawn = ItemPool[RandomIndex];

		if (ItemToSpawn) 
		{
			FVector SpawnLocation = GetActorLocation() + FVector(0.0f, 0.0f, 100.0f);
			FRotator SpawnRotation = FRotator::ZeroRotator;

			GetWorld()->SpawnActor<AActor>(ItemToSpawn, SpawnLocation, SpawnRotation);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Item pool is empty!"));
	}
}

void AlootChest::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
								bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && Cast<ACharacter>(OtherActor))
	{
		CanInteract = true;
	}
}

void AlootChest::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && Cast<ACharacter>(OtherActor))
	{
		CanInteract = false;
	}
}

