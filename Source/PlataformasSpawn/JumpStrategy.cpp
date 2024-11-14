// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpStrategy.h"
#include "Enemigo_Lobo.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AJumpStrategy::AJumpStrategy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJumpStrategy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJumpStrategy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJumpStrategy::ExecuteAction(AEnemigo_Lobo* Enemy)
{
    if (Enemy && Enemy->IsA(AEnemigo_Lobo::StaticClass()))
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Adding jump impulse to the lobo."));
        }
        UCharacterMovementComponent* CharacterMovement = Enemy->GetCharacterMovement();
        if (CharacterMovement)
        {
            FVector aux = GetActorLocation();
            FVector JumpImpulse = FVector(0.0f, 0.0f, 400.0f);
            SetActorLocation(aux + JumpImpulse);
            CharacterMovement->AddImpulse(aux, true);
        }
        else
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CharacterMovement component is missing!"));
            }
        }
    }
    else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemy reference is null or not of type AEnemigo_Lobo!"));
        }
    }
}

