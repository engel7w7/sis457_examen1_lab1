// Fill out your copyright notice in the Description page of Project Settings.

// publicador.cpp

#include "publicador.h"
#include "observador.h"

// Sets default values
Apublicador::Apublicador()
{
    PrimaryActorTick.bCanEverTick = true;
    observadores = TArray<AActor*>();
}

// Called when the game starts or when spawned
void Apublicador::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void Apublicador::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void Apublicador::agregarObservador(AActor* observador1)
{
    if (observador1 && !observadores.Contains(observador1))
    {
        observadores.Add(observador1);
    }
}

void Apublicador::quitarObservador(AActor* observador1)
{
    observadores.Remove(observador1);
}

void Apublicador::notificarObservadores()
{
    for (AActor* obs : observadores)
    {
        if (obs)
        {
            Iobservador* observador1 = Cast<Iobservador>(obs);
            if (observador1)
            {
                observador1->actualizar(this);
            }
            else
            {
                if (GEngine)
                {
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Fallo al hacer cast a Iobservador."));
                }
            }
        }
        else
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Observador es nulo."));
            }
        }
    }
}

