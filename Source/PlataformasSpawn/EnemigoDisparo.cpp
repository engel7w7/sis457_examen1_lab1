#include "EnemigoDisparo.h"
#include "Proyectil.h"
#include "Engine/World.h"
#include "TimerManager.h"

AEnemigoDisparo::AEnemigoDisparo()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		EnemigoDisparo(TEXT("StaticMesh'/Game/Geometry/CuboMesh/CuboStaticMesh.CuboStaticMesh'"));

	CuboMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CuboMesh"));
	CuboMesh->SetRelativeScale3D(FVector(1, 1, 1));
	CuboMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	CuboMesh->SetStaticMesh(EnemigoDisparo.Object);
	SetRootComponent(CuboMesh);

	Fire = FVector(0.0f, 1.0f, 0.0f); 
	FireRate = 0.5f;
	bCanFire = true;  
	bDisIz = false;	
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
		if (bDisIz)
		{
			Fire = FVector(0.0f, -1.0f, 0.0f);
		}
		else
		{
			Fire = FVector(0.0f, 1.0f, 0.0f);
		}
		bDisIz = !bDisIz;
		FVector SpawnLocation = GetActorLocation() + Fire * 100.0f;
		FRotator SpawnRotation = Fire.Rotation(); 
		GetWorld()->SpawnActor<Aproyectil>(ProyectilClase, SpawnLocation, SpawnRotation);
	}
}

void AEnemigoDisparo::ShotTimer()
{
	bCanFire = true;
}
