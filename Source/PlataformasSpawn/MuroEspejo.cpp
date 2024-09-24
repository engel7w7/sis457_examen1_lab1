// Fill out your copyright notice in the Description page of Project Settings.


#include "MuroEspejo.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Character.h"
#include "proyectil.h"  

AMuroEspejo::AMuroEspejo()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh>
        MeshEspejo(TEXT("StaticMesh'/Game/Geometry/MuroMesh/Muro_Espejo/MuroStaticMesh_Es.MuroStaticMesh_Es'"));
    if (MeshEspejo.Succeeded()) {
        MuroMesh->SetStaticMesh(MeshEspejo.Object);
    }
}

void AMuroEspejo::BeginPlay()
{
}

void AMuroEspejo::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

    if (Cast<Aproyectil>(OtherActor))
    {
        ReflectProjectile(OtherActor);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Reconoce"));
    }
}

void AMuroEspejo::ReflectProjectile(AActor* OtherActor)
{
    Aproyectil* Proyectil = Cast<Aproyectil>(OtherActor);
    if (Proyectil)
    {
        FVector Direction = Proyectil->GetActorForwardVector();
        FVector NewDirection = Direction * -1;
        Proyectil->SetActorRotation(NewDirection.Rotation());
        FVector SpawnOffset = NewDirection * 50.0f;
        Proyectil->SetActorLocation(Proyectil->GetActorLocation() + SpawnOffset);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Proyectil Reflejado"));
    }
}

