// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Muro.h"
#include "MuroEspejo.generated.h"

/**
 * 
 */
UCLASS()
class PLATAFORMASSPAWN_API AMuroEspejo : public AMuro
{
	GENERATED_BODY()
public:
	AMuroEspejo();
protected:
	virtual void BeginPlay();
	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	void ReflectProjectile(AActor* OtherActor);
};
