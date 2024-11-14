// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "publicador.generated.h"

UCLASS()
class PLATAFORMASSPAWN_API Apublicador : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    Apublicador();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    void agregarObservador(AActor* observador1);
    void quitarObservador(AActor* observador1);
    void notificarObservadores();

private:
    UPROPERTY()
    TArray<AActor*> observadores;
};

