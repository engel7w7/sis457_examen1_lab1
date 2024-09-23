#pragma once

#include "CoreMinimal.h"
#include "Muro.h"
#include "MuroCongelado.generated.h"

UCLASS()
class PLATAFORMASSPAWN_API AMuroCongelado : public AMuro
{
    GENERATED_BODY()

public:
    AMuroCongelado();

protected:
    virtual void BeginPlay() override;

    virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
