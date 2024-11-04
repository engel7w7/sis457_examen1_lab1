// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemigo.h"
#include "Enemigo_Lobo.h"
#include "Enemigo_Cuervo.h"
#include "FacadeTropa.generated.h"

UCLASS()
class PLATAFORMASSPAWN_API AFacadeTropa : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFacadeTropa();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	TArray<AEnemigo*> Tropa;
	float Timer;
public:
	void SpawnTropa(UWorld* World, TSubclassOf<AEnemigo> EnemyClass, FVector Location, int32 NumEnemies);
	void CommandTropa(FString Command);
};
