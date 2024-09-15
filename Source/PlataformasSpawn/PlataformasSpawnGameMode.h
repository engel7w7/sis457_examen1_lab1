// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlataformasSpawnGameMode.generated.h"

UCLASS(minimalapi)
class APlataformasSpawnGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APlataformasSpawnGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void GenerarEnemigos();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemigoDisparo> EnemigoClase;
	int MaxEnemigos, EnemigosGenerados;
	TArray<AEnemigoDisparo*> Enemigos;
	TMap<FString, AActor*> MapPlat;
	FVector Posicion;
	float PosicionAuxiliar;
	FRotator Rotacion;
	int spawnsPlataformas;
	float Time;
	int band;
	class ABarril* Ba;
	int cont;
	int32 aux1,aux2,aux3;
};



