// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemigo_Cuervo.h"

AEnemigo_Cuervo::AEnemigo_Cuervo()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshContainer(TEXT("SkeletalMesh'/Game/AnimalVarietyPack/Crow/Meshes/SK_Crow.SK_Crow'"));
	if (MeshContainer.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshContainer.Object);
	}
	bAtacando = false;
	TiempoPermanencia = 5.0f;
	DireccionDerecha = FVector(1.0f, 0.0f, 0.0f);
	DireccionIzquierda = FVector(-1.0f, 0.0f, 0.0f);
	Velocidad = 300.0f;
}
void AEnemigo_Cuervo::BeginPlay()
{
	Super::BeginPlay();
	PosicionInicial = GetActorLocation();
}

void AEnemigo_Cuervo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bAtacando)
	{
		FVector Direccion = (ObjetivoActual - GetActorLocation()).GetSafeNormal();
		AddMovementInput(Direccion, Velocidad);
	}
}

void AEnemigo_Cuervo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}

void AEnemigo_Cuervo::atacar()
{
	AActor* Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (Player)
	{
		ObjetivoActual = Player->GetActorLocation();
		bAtacando = true;

		GetWorldTimerManager().SetTimer(TimerHandle_Regreso, this, &AEnemigo_Cuervo::RegresarAPosicionInicial, TiempoPermanencia, false);
		GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Red, TEXT("Enemigo_Cuervo ataca"));
	}
}

void AEnemigo_Cuervo::mover()
{
	if (GetActorLocation().Equals(PosicionInicial + DireccionDerecha * 100.0f, 1.0f))
	{
		AddMovementInput(DireccionIzquierda, Velocidad);
	}
	else
	{
		AddMovementInput(DireccionDerecha, Velocidad);
	}
	GEngine->AddOnScreenDebugMessage(-1, 0.009f, FColor::White, TEXT("Enemigo_Cuervo se mueve de izquierda a derecha"));
}

void AEnemigo_Cuervo::aparecer(FVector Location)
{
	PosicionInicial = Location;
	SetActorLocation(Location);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Enemigo_Cuervo aparece"));
}

void AEnemigo_Cuervo::desaparecer()
{
	Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 0.009f, FColor::Yellow, TEXT("Enemigo_Cuervo desaparece"));
}

void AEnemigo_Cuervo::RegresarAPosicionInicial()
{
	ObjetivoActual = PosicionInicial;
	bAtacando = false;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Enemigo_Cuervo regresa a su posicion inicial"));
}