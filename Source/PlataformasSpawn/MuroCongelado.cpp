// Fill out your copyright notice in the Description page of Project Settings.


#include "MuroCongelado.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

AMuroCongelado::AMuroCongelado()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh>
        MeshCongelado(TEXT("StaticMesh'/Game/Geometry/MuroMesh/Muro_Congelante/MuroStaticMesh_Co.MuroStaticMesh_Co'"));
    if (MeshCongelado.Succeeded()) {
        MuroMesh->SetStaticMesh(MeshCongelado.Object);
    }
}

void AMuroCongelado::BeginPlay()
{
    Super::BeginPlay();
    MuroMesh->OnComponentBeginOverlap.AddDynamic(this, &AMuroCongelado::OnOverlapBegin);
    MuroMesh->OnComponentEndOverlap.AddDynamic(this, &AMuroCongelado::OnOverlapEnd);
}

void AMuroCongelado::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        ACharacter* Character = Cast<ACharacter>(OtherActor);
        if (Character)
        {
            Character->GetCharacterMovement()->MaxWalkSpeed *= 0.5f;
        }
    }
}

void AMuroCongelado::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        ACharacter* Character = Cast<ACharacter>(OtherActor);
        if (Character)
        {
            Character->GetCharacterMovement()->MaxWalkSpeed /= 0.5f;
        }
    }
}
