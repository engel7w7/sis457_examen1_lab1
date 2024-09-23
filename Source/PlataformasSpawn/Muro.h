// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Muro.generated.h"

UCLASS()
class PLATAFORMASSPAWN_API AMuro : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMuro();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* MuroMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* MuroCollision;

	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
