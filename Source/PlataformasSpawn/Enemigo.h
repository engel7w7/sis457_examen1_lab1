// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemigo.generated.h"

UCLASS()
class PLATAFORMASSPAWN_API AEnemigo : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemigo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	virtual void atacar() PURE_VIRTUAL(AEnemigo::atacar();)
	virtual void mover() PURE_VIRTUAL(AEnemigo::mover();)
	virtual void aparecer(FVector location) PURE_VIRTUAL(AEnemigo::aparecer(FVector location);)
	virtual void desaparecer() PURE_VIRTUAL(AEnemigo::desaparecer();)
	

};
