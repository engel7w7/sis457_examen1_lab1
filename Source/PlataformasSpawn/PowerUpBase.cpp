// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpBase.h"

// Sets default values
APowerUpBase::APowerUpBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    PowerUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerUpMesh"));
    RootComponent = PowerUpMesh;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Geometry/CuboMesh/ConoStaticMesh.ConoStaticMesh'"));
    if (MeshAsset.Succeeded())
    {
        PowerUpMesh->SetStaticMesh(MeshAsset.Object);
    }
}

// Called when the game starts or when spawned
void APowerUpBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerUpBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

