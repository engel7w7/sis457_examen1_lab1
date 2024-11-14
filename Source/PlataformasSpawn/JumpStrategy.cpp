// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpStrategy.h"
#include "Enemigo_Lobo.h"
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
    if (Enemy)
    {
        FVector JumpImpulse = FVector(0.0f, 0.0f, 600.0f);
        FVector Aux = FVector(0.f, 0.f, 200.f) + JumpImpulse;
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Adding jump impulse to the enemy."));
        }
        Enemy->GetCharacterMovement()->AddImpulse(Aux, true);
    }
    else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemy reference is null in JumpStrategy!"));
        }
    }
}

