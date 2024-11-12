// Fill out your copyright notice in the Description page of Project Settings.


#include "publicador.h"
#include "observador.h"
// Sets default values
Apublicador::Apublicador()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
	observadores.Add(observador1);
}

void Apublicador::quitarObservador(AActor* observador1)
{
	observadores.Remove(observador1);
}

void Apublicador::notificarObservadores() {
	for (AActor* obs : observadores)
	{
		Iobservador* observador1 = Cast<Iobservador>(obs);
		if (observador1)
		{
			observador1->actualizar(this);
		}
	}
}
