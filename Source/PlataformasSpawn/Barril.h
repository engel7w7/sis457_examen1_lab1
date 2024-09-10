// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Barril.generated.h"

UCLASS()
class PLATAFORMASSPAWN_API ABarril : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABarril();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	//Malla del barril
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* BarrilMesh;

	//Malla de colision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* BarrilColision;

	//Componente de velocidad
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UProjectileMovementComponent* BarrilMovement;
	// Velocidad de rotación
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movimiento")
	float RotationSpeed;

	// Aumentar la velocidad de movimiento en los rebotes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movimiento")
	float SpeedIncrease;

	// Velocidad máxima
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movimiento")
	float MaxSpeed;

	// Manejador de colisiones
	virtual void NotifyHit(
		class UPrimitiveComponent* MyComp,
		class AActor* Other,
		class UPrimitiveComponent* OtherComp,
		bool bSelfMoved,
		FVector HitLocation,
		FVector HitNormal,
		FVector NormalImpulse,
		const FHitResult& Hit
	) override;

};
