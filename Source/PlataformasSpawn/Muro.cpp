// Fill out your copyright notice in the Description page of Project Settings.


#include "Muro.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
// Sets default values
AMuro::AMuro()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		Muro(TEXT("StaticMesh'/Game/Geometry/MuroMesh/MuroStaticMesh.MuroStaticMesh'"));

	MuroMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Muro_Mesh"));
	MuroMesh->SetRelativeScale3D(FVector(1.5, 0.2, 1.7));
	MuroMesh->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	MuroMesh->SetStaticMesh(Muro.Object);
	SetRootComponent(MuroMesh);

	MuroCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Muro_collision"));
	MuroCollision->SetVisibility(true);
	MuroCollision->SetRelativeScale3D(FVector(2.f, 3.f, 1.60f));
	MuroCollision->SetCollisionProfileName(TEXT("Triger"));
	MuroCollision->SetupAttachment(GetRootComponent());

	MuroCollision->OnComponentBeginOverlap.AddDynamic(this, &AMuro::OnOverlapBegin);
	
	InitialLifeSpan = 40.f;
}

// Called when the game starts or when spawned
void AMuro::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMuro::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMuro::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Comportamiento por defecto
}
