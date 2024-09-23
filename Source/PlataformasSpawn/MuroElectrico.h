// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Muro.h"
#include "MuroElectrico.generated.h"

/**
 * 
 */
UCLASS()
class PLATAFORMASSPAWN_API AMuroElectrico : public AMuro
{
	GENERATED_BODY()
public:
	AMuroElectrico();
protected:
	virtual void BeginPlay();
	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
