// Fill out your copyright notice in the Description page of Project Settings.


#include "Barril.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABarril::ABarril()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		Barril(TEXT("StaticMesh'/Game/Geometry/BarrilMesh/BarrilStaticMesh.BarrilStaticMesh'"));
	BarrilMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barril_Mesh"));
	BarrilMesh->SetStaticMesh(Barril.Object);
	BarrilMesh->SetRelativeScale3D(FVector(0.4, 0.4, 0.4));
	BarrilMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	SetRootComponent(BarrilMesh);

	//MAlla de colisión
	BarrilColision = CreateAbstractDefaultSubobject<USphereComponent>(TEXT("BarrilColision"));
	BarrilColision->SetSphereRadius(255.0f);
	BarrilColision->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	BarrilColision->SetVisibility(true);
	BarrilColision->SetupAttachment(GetRootComponent());
	//MOvimiento
	BarrilMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BarrilMovement"));
	BarrilMovement->UpdatedComponent = BarrilMesh;
	BarrilMovement->InitialSpeed = 0.0f;  // Para controlar manualmente la velocidad de movimiento
	BarrilMovement->MaxSpeed = 1000.0f;  // Velocidad máxima
	BarrilMovement->bRotationFollowsVelocity = false;
	BarrilMovement->bShouldBounce = true;  // Permitir que rebote
	BarrilMovement->Bounciness = 0.7f;  // Configurar elasticidad
	BarrilMovement->Friction = 0.2f;
	RotationSpeed = 150.f;
}

// Called when the game starts or when spawned
void ABarril::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABarril::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Pitch += RotationSpeed * DeltaTime;

	if (CurrentRotation.Pitch > 360.0f)
	{
		CurrentRotation.Pitch -= 360.0f;
	}

	SetActorRotation(CurrentRotation);

}

void ABarril::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	// Aumentar la velocidad de movimiento al rebotar
	SpeedIncrease = 250.0f;  // Incremento en la velocidad
	FVector CurrentVelocity = BarrilMovement->Velocity;

	// Aumentar la magnitud de la velocidad, manteniendo la dirección
	FVector NewVelocity = CurrentVelocity.GetSafeNormal() * (CurrentVelocity.Size() + this->SpeedIncrease);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%s"), *NewVelocity.ToString()));

	// Aplicar la nueva velocidad, asegurándonos de no exceder la velocidad máxima
	if (NewVelocity.Size() <= BarrilMovement->MaxSpeed) {
		BarrilMovement->Velocity = NewVelocity;
	}
}

