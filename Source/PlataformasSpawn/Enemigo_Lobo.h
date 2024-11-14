// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "Enemigo_Lobo.generated.h"

UCLASS()
class PLATAFORMASSPAWN_API AEnemigo_Lobo : public AEnemigo
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemigo_Lobo();

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strategy")
	AActor* CurrentActionStrategy;
	void PerformAction();
	void SetActionStrategy(TSubclassOf<AActor> StrategyClass);
private:
	float time;
	FTimerHandle StrategyTimerHandle;
	void StartStrategyTimer();
	void ExecuteStrategyPeriodically();
	FVector PosicionI;
	FVector LimiteI;
	FVector LimiteF;
	FVector LimiteS;
	FVector LimiteSS;
	FVector posicionAc;
	FVector ObjetivoAc;
	float Velocidad;
	bool moverse;

};
