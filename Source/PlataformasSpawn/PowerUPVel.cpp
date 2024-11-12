// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUPVel.h"

// Sets default values
APowerUPVel::APowerUPVel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APowerUPVel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerUPVel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APowerUPVel::AplicarEfecto(APlataformasSpawnCharacter* Player)
{
	if (Player)
	{
		Player->IncrementarVelocidad();
		Destroy();
	}
}

