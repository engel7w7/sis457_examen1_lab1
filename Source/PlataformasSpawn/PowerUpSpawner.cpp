// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpSpawner.h"
#include "PowerUpBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"

// Sets default values
APowerUpSpawner::APowerUpSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SpawnInterval = 5.0f;
	SpawnAreaMin = FVector(-100.0f, -100.0f, 0.0f);
	SpawnAreaMax = FVector(100.0f, 100.0f, 0.0f);

}

// Called when the game starts or when spawned
void APowerUpSpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &APowerUpSpawner::SpawnPowerUp, SpawnInterval, true);
}

// Called every frame
void APowerUpSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APowerUpSpawner::SpawnPowerUp()
{
    if (PowerUpTypes.Num() > 0)
    {
        int32 Index = FMath::RandRange(0, PowerUpTypes.Num() - 1);
        TSubclassOf<APowerUpBase> SelectedPowerUpClass = PowerUpTypes[Index];

        FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(SpawnAreaMin, SpawnAreaMax);
        FRotator SpawnRotation = FRotator::ZeroRotator;

        GetWorld()->SpawnActor<APowerUpBase>(SelectedPowerUpClass, SpawnLocation, SpawnRotation);
    }
}

