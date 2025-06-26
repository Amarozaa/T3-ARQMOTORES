// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "lootChest.generated.h"

UCLASS()
class T3_ARQ_API AlootChest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AlootChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Base;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Tapa;

	UPROPERTY(EditAnywhere, Category = "Cofre")
	float anguloApertura = -110.f;

	UPROPERTY(EditAnywhere, Category = "Cofre")
	float velocidadApertura = 2.f;

	UPROPERTY(VisibleAnywhere, Category = "Trigger")
	class USphereComponent* TriggerSphere;

	bool IsOpen = false;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, 
						class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, 
					  class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(BlueprintReadOnly, Category = "Cofre")
	bool CanInteract = false;

	UFUNCTION(BlueprintCallable)
	void Interact();

	void SpawnLoot();

	UPROPERTY(EditAnywhere, Category = "Loot")
	TArray<TSubclassOf<AActor>> ItemPool;

private:
	FRotator InitialRotation;
	FRotator TargetRotation;
	float CurrentLerpAlpha;

};
