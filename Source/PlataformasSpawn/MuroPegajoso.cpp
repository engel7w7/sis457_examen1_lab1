
#include "MuroPegajoso.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

AMuroPegajoso::AMuroPegajoso()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh>
        MeshPegajoso(TEXT("StaticMesh'/Game/Geometry/MuroMesh/Muro_Pegajoso/MuroStaticMesh_Pe.MuroStaticMesh_Pe'"));
    if (MeshPegajoso.Succeeded()) {
        MuroMesh->SetStaticMesh(MeshPegajoso.Object);
    }
}

void AMuroPegajoso::BeginPlay()
{
    Super::BeginPlay();
    MuroMesh->OnComponentBeginOverlap.AddDynamic(this, &AMuroPegajoso::OnOverlapBegin);
}

void AMuroPegajoso::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        ACharacter* Character = Cast<ACharacter>(OtherActor);
        if (Character)
        {
            Character->GetCharacterMovement()->DisableMovement();
        }
    }
}
