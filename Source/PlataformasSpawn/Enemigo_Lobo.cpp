// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemigo_Lobo.h"
#include "EnemyActionStrategy.h"
#include "JumpStrategy.h"
#include "Engine/World.h"
#include "TimerManager.h"

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

	SetActionStrategy(AJumpStrategy::StaticClass());
	StartStrategyTimer();
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
void AEnemigo_Lobo::StartStrategyTimer()
{
	GetWorld()->GetTimerManager().SetTimer(StrategyTimerHandle,this,&AEnemigo_Lobo::ExecuteStrategyPeriodically,20.0f,true);
}
void AEnemigo_Lobo::PerformAction()
{
    if (CurrentActionStrategy && CurrentActionStrategy->GetClass()->ImplementsInterface(UEnemyActionStrategy::StaticClass()))
    {
        IEnemyActionStrategy* Action = Cast<IEnemyActionStrategy>(CurrentActionStrategy);
        if (Action)
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Executing strategy action on the enemy."));
            }
            Action->ExecuteAction(this);
        }
        else
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to cast to IEnemyActionInterface!"));
            }
        }
    }
    else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CurrentActionStrategy is null or does not implement the interface!"));
        }
    }
}

void AEnemigo_Lobo::ExecuteStrategyPeriodically()
{
	PerformAction();
}

void AEnemigo_Lobo::SetActionStrategy(TSubclassOf<AActor> StrategyClass)
{
    if (CurrentActionStrategy)
    {
        CurrentActionStrategy->Destroy();
    }
    CurrentActionStrategy = GetWorld()->SpawnActor<AActor>(StrategyClass, FVector::ZeroVector, FRotator::ZeroRotator);

    if (CurrentActionStrategy)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
                FString::Printf(TEXT("Strategy created successfully: %s"), *CurrentActionStrategy->GetName()));
        }
    }
    else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to create strategy!"));
        }
    }
}


