// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerObservador.h"
#include "Enemigo_Lobo.h"
#include "publicador.h"

// Sets default values
ASpawnerObservador::ASpawnerObservador()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnerObservador::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnerObservador::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASpawnerObservador::actualizar(Apublicador* publicador)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Metodo actualizar llamado"));
    }

    if (EnemyClass != nullptr)
    {
        UWorld* world = GetWorld();
        if (world)
        {
            FVector SpawnLocation = GetActorLocation() + FVector(FMath::RandRange(-300.0f, 300.0f), FMath::RandRange(-300.0f, 300.0f), 50.0f);
            FRotator SpawnRotation = FRotator::ZeroRotator;

            AEnemigo_Lobo* NewEnemy = world->SpawnActor<AEnemigo_Lobo>(EnemyClass, SpawnLocation, SpawnRotation);

            if (NewEnemy)
            {
                if (GEngine)
                {
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Enemy spawned at location: %s"), *SpawnLocation.ToString()));
                }
            }
            else
            {
                if (GEngine)
                {
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to spawn enemy."));
                }
            }
        }
    }
    else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("EnemyClass is null."));
        }
    }
}
