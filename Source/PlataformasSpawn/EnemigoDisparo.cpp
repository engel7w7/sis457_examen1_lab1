#include "EnemigoDisparo.h"
#include "Proyectil.h"
#include "Engine/World.h"
#include "TimerManager.h"

AEnemigoDisparo::AEnemigoDisparo()
{
    PrimaryActorTick.bCanEverTick = true;

    // Encontrar la malla del enemigo
    static ConstructorHelpers::FObjectFinder<UStaticMesh>
        EnemigoDisparo(TEXT("StaticMesh'/Game/Geometry/CuboMesh/ConoStaticMesh.ConoStaticMesh'"));

    CuboMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CuboMesh"));
    CuboMesh->SetRelativeScale3D(FVector(1, 1, 1));
    CuboMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
    CuboMesh->SetStaticMesh(EnemigoDisparo.Object);
    SetRootComponent(CuboMesh);

    FireRate = 0.5f;
    bCanFire = true;
    FireDirectionIndex = 0;
    static ConstructorHelpers::FClassFinder<Aproyectil> ProyectilClassFinder(TEXT("Class'/Script/PlataformasSpawn.proyectil'"));
    if (ProyectilClassFinder.Succeeded())
    {
        ProyectilClase = ProyectilClassFinder.Class;
    }
}

void AEnemigoDisparo::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AEnemigoDisparo::ShotTimer, FireRate, true);
}

void AEnemigoDisparo::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bCanFire)
    {
        FireShot();
        bCanFire = false;
    }
}

void AEnemigoDisparo::FireShot()
{
    if (ProyectilClase)
    {
        switch (FireDirectionIndex)
        {
        case 0:
            Fire = FVector(0.0f, 1.0f, 0.0f);
            break;
        case 1:
            Fire = FVector(0.0f, -1.0f, 0.0f);
            break;
        case 2:
            Fire = FVector(0.0f, 0.0f, 1.0f);
            break;
        case 3:
            Fire = FVector(0.0f, 0.0f, -1.0f);
            break;
        }
        FireDirectionIndex = (FireDirectionIndex + 1) % 4;

        FVector SpawnLocation = GetActorLocation() + Fire * 100.0f;
        FRotator SpawnRotation = Fire.Rotation();
        GetWorld()->SpawnActor<Aproyectil>(ProyectilClase, SpawnLocation, SpawnRotation);
    }
}

void AEnemigoDisparo::ShotTimer()
{
    bCanFire = true;
}
