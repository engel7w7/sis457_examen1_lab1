// Fill out your copyright notice in the Description page of Project Settings.

#include "proyectil.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
Aproyectil::Aproyectil()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Initialize and set the collision sphere as the root component
    ColisionEsfera = CreateDefaultSubobject<USphereComponent>(TEXT("ColisionEsfera"));
    ColisionEsfera->InitSphereRadius(10.0f);
    //ColisionEsfera->SetCollisionProfileName(TEXT("BlockAllDynamic"));
    ColisionEsfera->SetCollisionProfileName(TEXT("NoCollision"));  // Prueba sin colisiones
    RootComponent = ColisionEsfera;

    // Initialize and attach the projectile mesh to the root component
    ProyectilMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Proyectil_Mesh"));
    ProyectilMesh->SetupAttachment(RootComponent); // Attach to the collision sphere
    ProyectilMesh->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));
    ProyectilMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Geometry/CocoMesh/CocoStaticMesh.CocoStaticMesh'")).Object);

    // Initialize and configure the projectile movement component
    MovimientoProyectil = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovimientoProyectil"));
    MovimientoProyectil->InitialSpeed = 400.0f;
    MovimientoProyectil->MaxSpeed = 800.0f;

    // Bind the OnHit event
    ColisionEsfera->OnComponentHit.AddDynamic(this, &Aproyectil::OnHit);

    // Set the lifespan of the projectile
    InitialLifeSpan = 2.0f;
}

// Called when the game starts or when spawned
void Aproyectil::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void Aproyectil::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void Aproyectil::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && (OtherActor != this) && OtherComp && OtherComp->IsSimulatingPhysics())
    {
        OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
    }
    Destroy();
}
