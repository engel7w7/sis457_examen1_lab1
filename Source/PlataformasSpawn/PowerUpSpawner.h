// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUpSpawner.generated.h"

UCLASS()
class PLATAFORMASSPAWN_API APowerUpSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUpSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere, Category = "PowerUps")
	TArray<TSubclassOf<class APowerUpBase>> PowerUpTypes;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float SpawnInterval = 10.0f;
	UPROPERTY(EditAnywhere, Category = "Spawning")
	FVector SpawnAreaMin;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	FVector SpawnAreaMax;
private:
	void SpawnPowerUp();

	FTimerHandle SpawnTimer;

};
