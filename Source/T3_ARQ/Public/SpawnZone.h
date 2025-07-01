// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnZone.generated.h"

UCLASS()
class T3_ARQ_API ASpawnZone : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Volumen visible en el editor
	UPROPERTY(VisibleAnywhere, Category = "Spawn")
	class UBoxComponent* VisualBox;



	// Clase del cofre a spawnear (único tipo)
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> ChestClass;


	UPROPERTY(EditAnywhere, Category = "Spawn")
	int32 SpawnCount = 5;

	// Offset vertical para raycast
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float TraceZStart = -1000.0f;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float TraceZEnd = 3000.0f;

	// Función de spawn
	void SpawnRandomActors();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
