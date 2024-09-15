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
    ColisionEsfera->SetCollisionProfileName(TEXT("BlockAllDynamic"));
    //ColisionEsfera->SetCollisionProfileName(TEXT("NoCollision"));
    RootComponent = ColisionEsfera;

    // Initialize and attach the projectile mesh to the root component
    ProyectilMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Proyectil_Mesh"));
    ProyectilMesh->SetupAttachment(RootComponent);
    ProyectilMesh->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));
    ProyectilMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Geometry/CocoMesh/CocoStaticMesh.CocoStaticMesh'")).Object);

    // Initialize and configure the projectile movement component
    MovimientoProyectil = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovimientoProyectil"));
    MovimientoProyectil->InitialSpeed = 1500.0f;
    MovimientoProyectil->MaxSpeed = 2500.0f;
    ColisionEsfera->OnComponentHit.AddDynamic(this, &Aproyectil::OnHit);
    InitialLifeSpan = 0.5f;
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
