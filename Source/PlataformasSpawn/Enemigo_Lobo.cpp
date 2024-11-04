// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemigo_Lobo.h"

// Sets default values
AEnemigo_Lobo::AEnemigo_Lobo()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshContainer(TEXT("SkeletalMesh'/Game/AnimalVarietyPack/Wolf/Meshes/SK_Wolf.SK_Wolf'"));
	if (MeshContainer.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshContainer.Object);
	}

}

// Called when the game starts or when spawned
void AEnemigo_Lobo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemigo_Lobo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemigo_Lobo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AEnemigo_Lobo::atacar()
{
}

void AEnemigo_Lobo::mover()
{
}

void AEnemigo_Lobo::aparecer(FVector Location)
{
}

void AEnemigo_Lobo::desaparecer()
{
}

