// Fill out your copyright notice in the Description page of Project Settings.


#include "BasedeProjectile.h"

// Sets default values
ABasedeProjectile::ABasedeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
    CollisionComp->InitSphereRadius(10.f);
    CollisionComp->SetCollisionProfileName("BlockAllDynamic");
    CollisionComp->SetNotifyRigidBodyCollision(true);
    CollisionComp->SetGenerateOverlapEvents(true);
    RootComponent = CollisionComp;

    CollisionComp->OnComponentHit.AddDynamic(this, &ABasedeProjectile::OnHit);

     // Movimiento
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 2000.f;
    ProjectileMovement->MaxSpeed = 2000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->ProjectileGravityScale = 0.f;

	//Stats iniciales
    Range = 500.f;
    AttackDamage = 1.f;


    NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
    NiagaraComp->SetupAttachment(RootComponent);
    NiagaraComp->bAutoActivate = true;

}

// Called when the game starts or when spawned
void ABasedeProjectile::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();

    if (NiagaraEffect)
    {
        NiagaraComp->SetAsset(NiagaraEffect);
        NiagaraComp->Activate(true);
    }
	
}

// Called every frame
void ABasedeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Se revisa que el proyectil no recorra una distancia mayor a la especificada
	float DistanceTraveled = FVector::Dist(InitialLocation, GetActorLocation());
    if (DistanceTraveled >= Range)
    {
        Explode();
    }
    
    // Actualizar la posición de la partícula
    if (NiagaraComp && NiagaraEffect)
    {
        NiagaraComp->SetWorldLocation(GetActorLocation());
        NiagaraComp->SetWorldRotation(GetActorRotation());
	}
}

void ABasedeProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse,
    const FHitResult& Hit)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("miau"));

    Explode();
}

void ABasedeProjectile::Explode()
{
    if (ExplosionEffect)
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            ExplosionEffect,
            GetActorLocation(),
            GetActorRotation() // o simplemente FRotator::ZeroRotator
        );
    }
    Destroy();
}

