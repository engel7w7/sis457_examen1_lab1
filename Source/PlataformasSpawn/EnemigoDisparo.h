#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemigoDisparo.generated.h"

UCLASS()
class PLATAFORMASSPAWN_API AEnemigoDisparo : public AActor
{
	GENERATED_BODY()

public:
	AEnemigoDisparo();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Disparo")
	UStaticMeshComponent* CuboMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Disparo")
	TSubclassOf<class Aproyectil> ProyectilClase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Disparo")
	FVector Fire;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Disparo")
	float FireRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Disparo")
	uint32 bCanFire : 1;
	void FireShot();
	FTimerHandle TimerHandle_ShotTimerExpired;
	void ShotTimer();
	bool bDisIz;
};
