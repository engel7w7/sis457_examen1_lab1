// Fill out your copyright notice in the Description page of Project Settings.

#include "ProyectilAdaptado.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/World.h"


// Sets default values
AProyectilAdaptado::AProyectilAdaptado()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (GetWorld())
	{
		ProyectilExterno = GetWorld()->SpawnActor<AADAPTER_GALAGA_L08Projectile>(AADAPTER_GALAGA_L08Projectile::StaticClass()); //6.- llamamos a un proyectil y lo 
	}
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Geometry/CocoMesh/CocoStaticMesh.CocoStaticMesh'"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(MeshAsset.Object);
	}
}

// Called when the game starts or when spawned
void AProyectilAdaptado::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProyectilAdaptado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AProyectilAdaptado::cargar()
{
	ProyectilExterno->SetActorLocation(GetActorLocation());
}
void AProyectilAdaptado::SetProjectile(AADAPTER_GALAGA_L08Projectile* InProjectile) 
{ 
	ProyectilExterno = InProjectile;
} 