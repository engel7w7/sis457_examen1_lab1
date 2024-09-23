// MuroPegajoso.h
#pragma once

#include "CoreMinimal.h"
#include "Muro.h"
#include "MuroPegajoso.generated.h"

UCLASS()
class PLATAFORMASSPAWN_API AMuroPegajoso : public AMuro
{
    GENERATED_BODY()

public:
    AMuroPegajoso();

protected:
    virtual void BeginPlay() override;

    virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
