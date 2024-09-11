// Fill out your copyright notice in the Description page of Project Settings.


#include "Plataformas.h"

// Sets default values
APlataformas::APlataformas()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> 
		Plataforma(TEXT("StaticMesh'/Game/Geometry/PlataformaMesh/uploads_files_4917076_picatinny_deck_l.uploads_files_4917076_picatinny_deck_l'"));

	PlataformaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plataforma_Mesh"));
	PlataformaMesh->SetRelativeScale3D(FVector(1.5, 1.7, 1.5));
	PlataformaMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	PlataformaMesh->SetStaticMesh(Plataforma.Object);
	SetRootComponent(PlataformaMesh);
	LimiteSuperior = 200.0f;
	LimiteInferior = 0.0f;
	velocidad = 50.f;
	DireccionMovimiento = FVector(0.f, 0.f, 1.f);
}

// Called when the game starts or when spawned
void APlataformas::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlataformas::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (mover == true)
	{
		FVector NuevaPosicion = GetActorLocation() + (DireccionMovimiento * DeltaTime *velocidad);
		if (NuevaPosicion.Z >= LimiteSuperior || NuevaPosicion.Z <= LimiteInferior)
		{
			DireccionMovimiento *= -1;
		}

		SetActorLocation(NuevaPosicion);
	}
	
}

