// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventario.h"

// Sets default values
AInventario::AInventario()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInventario::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInventario::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

