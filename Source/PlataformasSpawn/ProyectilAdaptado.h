// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ADAPTER_GALAGA_L08Projectile.h"
#include "AdaptadorInterface.h"
#include "ProyectilAdaptado.generated.h"

UCLASS()
class PLATAFORMASSPAWN_API AProyectilAdaptado : public AActor, public IAdaptadorInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProyectilAdaptado();
public:
	virtual void cargar() override; // 2.-funcion virtual desde la interf
	void SetProjectile(AADAPTER_GALAGA_L08Projectile* InProjectile);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//IAdaptadorInterface* proyectilExterno; // 3.-puntero para 
	UProjectileMovementComponent* ProjectileMovement; // Asegúrate de que esta línea esté presente
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UStaticMeshComponent* StaticMeshComponent;
	AADAPTER_GALAGA_L08Projectile* ProyectilExterno; //5.- con un puntero de galaga creamos una direccion
};
