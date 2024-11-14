// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "Enemigo_Cuervo.generated.h"

/**
 * 
 */
UCLASS()
class PLATAFORMASSPAWN_API AEnemigo_Cuervo : public AEnemigo
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AEnemigo_Cuervo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void atacar() override;
	virtual void mover() override;
	virtual void aparecer(FVector Location) override;
	virtual void desaparecer() override;
protected:
	FVector PosicionI;
	FVector LimiteI;
	FVector LimiteF;
	FVector posicionAc;
	FVector ObjetivoAc;
	float Velocidad;
	bool moverse;
};
