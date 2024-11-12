// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUpBase.h"
#include "PowerUPVel.generated.h"

UCLASS()
class PLATAFORMASSPAWN_API APowerUPVel : public APowerUpBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUPVel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void AplicarEfecto(APlataformasSpawnCharacter* Player) override;

};
