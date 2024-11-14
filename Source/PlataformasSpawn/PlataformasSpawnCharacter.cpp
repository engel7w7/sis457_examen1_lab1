// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlataformasSpawnCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ProyectilADaptado.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


void APlataformasSpawnCharacter::BeginPlay()
{
   /* Super::BeginPlay();
        TArray<AActor*> FoundActors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), Apublicador::StaticClass(), FoundActors);
        if (FoundActors.Num() > 0)
        {
            publicador = Cast<Apublicador>(FoundActors[0]);
            if (publicador)
            {
                publicador->agregarObservador(this);
            }
            else
            {
                if (GEngine)
                {
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Fallo al inicializar publicador."));
                }
            }
        }*/
}

APlataformasSpawnCharacter::APlataformasSpawnCharacter()
{
    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Don't rotate when the controller rotates
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;


    // Create a camera boom attached to the root (capsule)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
    CameraBoom->bDoCollisionTest = false;
    CameraBoom->TargetArmLength = 1200.f;
    CameraBoom->SocketOffset = FVector(0.f, 0.f, 75.f);
    CameraBoom->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

    // Create a camera and attach to boom
    SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
    SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // Rotation rate
    GetCharacterMovement()->GravityScale = 2.f;
    GetCharacterMovement()->AirControl = 0.80f;
    GetCharacterMovement()->JumpZVelocity = 2000.f;
    GetCharacterMovement()->GroundFriction = 3.f;
    GetCharacterMovement()->MaxWalkSpeed = 600.f;
    GetCharacterMovement()->MaxFlySpeed = 600.f;


    ClaseProyectil = AProyectilAdaptado::StaticClass();
    VelocidadBase = 600.0f;
    //SaltoBase = 600.0f;
    //Apublicador* publicador;
    MultiplicadorVelocidad = 1.5f;
    //MultiplicadorSalto = 1.3f;

    DuracionPowerUp = 10.0f;
}

void APlataformasSpawnCharacter::IncrementarVelocidad()
{
    GetCharacterMovement()->MaxWalkSpeed = VelocidadBase * MultiplicadorVelocidad;

    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlataformasSpawnCharacter::RevertirVelocidad, DuracionPowerUp, false);

}
/*
void APlataformasSpawnCharacter::IncrementarSalto()
{
    GetCharacterMovement()->JumpZVelocity = SaltoBase * MultiplicadorSalto;

    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlataformasSpawnCharacter::RevertirSalto, DuracionPowerUp, false);

}
*/
void APlataformasSpawnCharacter::RevertirVelocidad()
{
    GetCharacterMovement()->MaxWalkSpeed = VelocidadBase;
}
/*
void APlataformasSpawnCharacter::RevertirSalto()
{
    GetCharacterMovement()->JumpZVelocity = SaltoBase;
}
*/
//////////////////////////////////////////////////////////////////////////
// Input

void APlataformasSpawnCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    // Set up gameplay key bindings
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("fire", IE_Pressed, this, &APlataformasSpawnCharacter::DispararProyectil);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    PlayerInputComponent->BindAxis("MoveRight", this, &APlataformasSpawnCharacter::MoveRight);
    PlayerInputComponent->BindTouch(IE_Pressed, this, &APlataformasSpawnCharacter::TouchStarted);
    PlayerInputComponent->BindTouch(IE_Released, this, &APlataformasSpawnCharacter::TouchStopped);
}

void APlataformasSpawnCharacter::MoveRight(float Value)
{
    // Add movement in that direction
    AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
}

void APlataformasSpawnCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
    // Jump on any touch
    Jump();
}

void APlataformasSpawnCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
    StopJumping();
}
/*
void APlataformasSpawnCharacter::PostInitializeComponents()
{
   Super::PostInitializeComponents();
   SetActorLocation(FVector(1180.f, -1700.f, 3600.f));
}
*/
void APlataformasSpawnCharacter::DispararProyectil()
{
    if (ClaseProyectil)
    {
        FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 250.f;
        FRotator SpawnRotation = GetActorRotation();

        UWorld* World = GetWorld();
        if (World)
        {
            AProyectilAdaptado* ProjectilAdaptado = World->SpawnActor<AProyectilAdaptado>(ClaseProyectil, SpawnLocation, SpawnRotation);
        	if (ProjectilAdaptado)
			{
				ProjectilAdaptado->cargar();
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Disparo"));
			}
        }    
    }
}
