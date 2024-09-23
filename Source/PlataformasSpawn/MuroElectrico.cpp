#include "MuroElectrico.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Character.h"

AMuroElectrico::AMuroElectrico()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh>
        MeshElectrico(TEXT("StaticMesh'/Game/Geometry/MuroMesh/Muro_Electrico/MuroStaticMesh_El.MuroStaticMesh_El'"));
    if (MeshElectrico.Succeeded()) {
        MuroMesh->SetStaticMesh(MeshElectrico.Object);
    }
}

void AMuroElectrico::BeginPlay()
{
    Super::BeginPlay();
}

void AMuroElectrico::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

    if (OtherActor && (OtherActor != this) && OtherComp)
    {

        ACharacter* Character = Cast<ACharacter>(OtherActor);
        if (Character)
        {
            Character->Destroy();
        }
    }
}
