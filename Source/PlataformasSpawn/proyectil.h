// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "proyectil.generated.h"

UCLASS()
class PLATAFORMASSPAWN_API Aproyectil : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aproyectil();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ProyectilMesh;

	UPROPERTY(VisibleAnywhere, Category = "Componentes")
	class USphereComponent* ColisionEsfera;

	UPROPERTY(VisibleAnywhere, Category = "Movimiento")
	class UProjectileMovementComponent* MovimientoProyectil;

};
