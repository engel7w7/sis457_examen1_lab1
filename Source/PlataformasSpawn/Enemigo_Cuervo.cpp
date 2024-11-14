// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemigo_Cuervo.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AEnemigo_Cuervo::AEnemigo_Cuervo()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshContainer(TEXT("SkeletalMesh'/Game/AnimalVarietyPack/Crow/Meshes/SK_Crow.SK_Crow'"));
	if (MeshContainer.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshContainer.Object);
	}
	Velocidad = 2.5f;
	moverse = true;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	PosicionI = GetActorLocation();
	LimiteI = PosicionI + FVector(0, 600, 0);
	LimiteF = PosicionI + FVector(0, -600, 0);
}
void AEnemigo_Cuervo::BeginPlay()
{
	Super::BeginPlay();
	PosicionI = GetActorLocation();
}

void AEnemigo_Cuervo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemigo_Cuervo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}

void AEnemigo_Cuervo::atacar()
{
	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (Player)
	{
		FVector Direction = (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		FVector NewLocation = GetActorLocation() + (Direction * 7.5f);
		SetActorLocation(NewLocation);

		FRotator NewRotation = Direction.Rotation();
		NewRotation.Pitch = FMath::RandRange(-10.0f, 10.0f);
		NewRotation.Roll = FMath::RandRange(-10.0f, 10.0f); 
		NewRotation.Yaw > 0 ? NewRotation.Yaw = 0 : NewRotation.Yaw = 180;
		SetActorRotation(NewRotation);

		GetWorld()->GetTimerManager().SetTimer(Timer, this, &AEnemigo_Cuervo::atacar, FMath::RandRange(0.007f, 0.012f), true); 
		GEngine->AddOnScreenDebugMessage(-1, 0.009f, FColor::Yellow, TEXT("Enemigo Cuervo ataca"));
	}

}

void AEnemigo_Cuervo::mover()
{
	posicionAc = GetActorLocation();
	if (moverse)
	{
		if (posicionAc.Y <= LimiteI.Y) {
			posicionAc.Y += Velocidad * FMath::RandRange(0.8f, 1.2f);
		}
		else moverse = false;
	}
	else
	{
		if (posicionAc.Y >= LimiteF.Y) {
			posicionAc.Y -= Velocidad * FMath::RandRange(0.8f, 1.2f);
		}
		else moverse = true;
	}
	SetActorLocation(posicionAc);
	float TimerInterval = FMath::RandRange(0.001f, 0.003f);
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AEnemigo_Cuervo::mover, TimerInterval, true);
	GEngine->AddOnScreenDebugMessage(-1, 0.007f, FColor::Yellow, FString::Printf(TEXT("Enemigo Cuervo se mueve: %s"), *posicionAc.ToString()));
}

void AEnemigo_Cuervo::aparecer(FVector Location)
{
	PosicionI = Location;
	SetActorLocation(Location);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Enemigo_Cuervo aparece"));
}

void AEnemigo_Cuervo::desaparecer()
{
	Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 0.009f, FColor::Yellow, TEXT("Enemigo_Cuervo desaparece"));
}
