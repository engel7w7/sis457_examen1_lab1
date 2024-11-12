// Fill out your copyright notice in the Description page of Project Settings.


#include "FacadeTropa.h"

// Sets default values
AFacadeTropa::AFacadeTropa()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Timer = 0.0f;
}

// Called when the game starts or when spawned
void AFacadeTropa::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFacadeTropa::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    Timer += DeltaTime;
    GEngine->AddOnScreenDebugMessage(-1, 0.008f, FColor::Red, FString::Printf(TEXT("Timer: %f"), Timer));

    if (Timer >= 15.0f && Timer < 25.0f)
    {
        CommandTropa("Moverse");
    }
    else if (Timer >= 25.0f && Timer < 35.0f)
    {
        CommandTropa("Atacar");
    }
    else if (Timer >= 35.0f)
    {
        CommandTropa("Desaparecer");
    }
}

void AFacadeTropa::SpawnTropa(UWorld* World, TSubclassOf<AEnemigo> EnemyClass, FVector Location, int32 NumEnemies)
{
    if (World)
    {
        for (int32 i = 0; i < NumEnemies; ++i)
        {
            FVector SpawnLocation = Location + FVector(0.0f, 0.0f, i*550.0f);
            FActorSpawnParameters SpawnParams;
            AEnemigo* NewEnemy = World->SpawnActor<AEnemigo>(EnemyClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
            if (NewEnemy)
            {
                NewEnemy->aparecer(SpawnLocation);
                Tropa.Add(NewEnemy);
            }
        }
    }
}

void AFacadeTropa::CommandTropa(FString Command)
{
    for (AEnemigo* Enemy : Tropa)
    {
        if (Enemy)
        {
            if (Command == "Atacar")
            {
                Enemy->atacar();
            }
            else if (Command == "Moverse")
            {
                Enemy->mover();
            }
            else if (Command == "Desaparecer")
            {
                Enemy->desaparecer();
            }
        }
    }
}

