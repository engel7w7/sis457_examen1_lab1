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
protected:

	UPROPERTY(VisibleAnywhere, Category = "Eventos")
	TArray<AActor*> observadores; //Arreglo de observadores
public:
	void agregarObservador(AActor* observador1); //Funcion para agregar observadores
	void quitarObservador(AActor* observador1); //Funcion para quitar observadores
	void notificarObservadores(); //Funcion para notificar a los observadores
};
