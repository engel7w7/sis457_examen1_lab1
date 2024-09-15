#include "PlataformasSpawnGameMode.h"
#include "PlataformasSpawnCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Plataformas.h"
#include "Barril.h"
#include "EnemigoDisparo.h"
#include "Engine/World.h"
#include "TimerManager.h"

APlataformasSpawnGameMode::APlataformasSpawnGameMode()
{
    PrimaryActorTick.bCanEverTick = true;
    FMath::RandInit(FDateTime::Now().GetMillisecond());

    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
    if (PlayerPawnBPClass.Class != nullptr)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }

    Posicion = FVector(1180.f, 1100.f, 140.f);
    Rotacion = FRotator(0.0f, 0.0f, 0.0f);
    PosicionAuxiliar = 875.f;
    Time = 0.0f;
    spawnsPlataformas = 0;
    band = 0;
    cont = 0;

    MaxEnemigos = 3;
    EnemigosGenerados = 0;
    static ConstructorHelpers::FClassFinder<AEnemigoDisparo> ProyectilClassFinder(TEXT("Class'/Script/PlataformasSpawn.EnemigoDisparo'"));
    if (ProyectilClassFinder.Succeeded())
    {
        EnemigoClase = ProyectilClassFinder.Class;
    }

}

void APlataformasSpawnGameMode::BeginPlay()
{
    Super::BeginPlay();
    FMath::RandInit(FDateTime::Now().GetMillisecond());

    for (int i = 0; i < 5; i++) {
        if (band == 0)
        {
            Rotacion = FRotator(0.0f, 0.0f, 0.f);
            PosicionAuxiliar *= -1;
            band = 1;
            for (int j = 0; j < 3; j++)
            {
                APlataformas* Plataforma = GetWorld()->SpawnActor<APlataformas>(APlataformas::StaticClass(), Posicion, Rotacion);
                FString Key = FString::Printf(TEXT("Plataforma%d"), cont++);
                MapPlat.Add(Key, Plataforma);
                Posicion.Y += PosicionAuxiliar;
            }
            Posicion.Z += 600.0f;
            Posicion.Y *= (-1);
        }
        else
        {
            Rotacion = FRotator(0.0f, 0.0f, -6.f);
            PosicionAuxiliar *= -1;
            band = 0;
            for (int j = 0; j < 3; j++)
            {
                APlataformas* Plataforma = GetWorld()->SpawnActor<APlataformas>(APlataformas::StaticClass(), Posicion, Rotacion);
                FString Key = FString::Printf(TEXT("Plataforma%d"), cont++);
                MapPlat.Add(Key, Plataforma);
                Posicion.Y -= PosicionAuxiliar;
                Posicion.Z -= 80.f;
            }
            Posicion.Z += 240.f;
            Posicion.Z += 600.0f;
            Posicion.Y *= (-1);
        }
    }
    do {
        aux1 = FMath::RandRange(0, MapPlat.Num() - 1);
        aux2 = FMath::RandRange(0, MapPlat.Num() - 1);
        aux3 = FMath::RandRange(0, MapPlat.Num() - 1);
    } while (aux1 == aux2 || aux1 == aux3 || aux2 == aux3);
    
    FString Key1 = FString::Printf(TEXT("Plataforma%d"), aux1);
    FString Key2 = FString::Printf(TEXT("Plataforma%d"), aux2);
    FString Key3 = FString::Printf(TEXT("Plataforma%d"), aux3);

    if (MapPlat.Contains(Key1)) {
        APlataformas* Plataforma1 = Cast<APlataformas>(MapPlat[Key1]);
        if (Plataforma1) {
            Plataforma1->setmover(true);
            if (GEngine) {
                GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Plataforma %s se está moviendo"), *Key1));
            }
        }
    }
    if (MapPlat.Contains(Key2)) {
        APlataformas* Plataforma2 = Cast<APlataformas>(MapPlat[Key2]);
        if (Plataforma2) {
            Plataforma2->setmover(true);
            if (GEngine) {
                GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Plataforma %s se está moviendo"), *Key2));
            }
        }
    }
    if (MapPlat.Contains(Key3)) {
        APlataformas* Plataforma3 = Cast<APlataformas>(MapPlat[Key3]);
        if (Plataforma3) {
            Plataforma3->setmover(true);
            if (GEngine) {
                GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Plataforma %s se está moviendo"), *Key3));
            }
        }
    }
    GenerarEnemigos();
}

void APlataformasSpawnGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APlataformasSpawnGameMode::GenerarEnemigos()
{
    while (EnemigosGenerados < MaxEnemigos)
    {
        int32 PlataformaIndex = FMath::RandRange(0, MapPlat.Num() - 1);
        FString Key = FString::Printf(TEXT("Plataforma%d"), PlataformaIndex);

        if (MapPlat.Contains(Key))
        {
            APlataformas* Plataforma = Cast<APlataformas>(MapPlat[Key]);
            if (Plataforma)
            {
                FVector EnemigoPosicion = Plataforma->GetActorLocation() + FVector(0, 0, 200);
                AEnemigoDisparo* Enemigo = GetWorld()->SpawnActor<AEnemigoDisparo>(EnemigoClase, EnemigoPosicion, FRotator::ZeroRotator);
                 Enemigos.Add(Enemigo);
                    EnemigosGenerados++;
            }
        }
    }
}
