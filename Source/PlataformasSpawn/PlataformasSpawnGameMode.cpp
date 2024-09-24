#include "PlataformasSpawnGameMode.h"
#include "PlataformasSpawnCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Plataformas.h"
#include "Barril.h"
#include "EnemigoDisparo.h"
#include "Muro.h"
#include "MuroCongelado.h"  
#include "MuroLadrillo.h"
#include "MuroPegajoso.h"
#include "MuroElectrico.h"
#include "MuroEspejo.h" 
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

    Posicion = FVector(1180.f, 3300.f, 140.f);
    Rotacion = FRotator(0.0f, 0.0f, 0.0f);
    PosicionAuxiliar = 690.f;
    Time = 0.0f;
    spawnsPlataformas = 0;
    band = 0;
    cont = 0;

    MaxEnemigos = 5;
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
            for (int j = 0; j < 10; j++)
            {
                APlataformas* Plataforma = GetWorld()->SpawnActor<APlataformas>(APlataformas::StaticClass(), Posicion, Rotacion);
                //FString Key = FString::Printf(TEXT("Plataforma%d"), cont++);
                //MapPlat.Add(Key, Plataforma);
                MapPlat.Add(Plataforma);
                Posicion.Y += PosicionAuxiliar;
            }
            Posicion.Z += 1100.0f;
            Posicion.Y *= (-1);
        }
        else
        {
            Rotacion = FRotator(0.0f, 0.0f, -6.f);
            PosicionAuxiliar *= -1;
            band = 0;
            for (int j = 0; j < 10; j++)
            {
                APlataformas* Plataforma = GetWorld()->SpawnActor<APlataformas>(APlataformas::StaticClass(), Posicion, Rotacion);
                //FString Key = FString::Printf(TEXT("Plataforma%d"), cont++);
                //MapPlat.Add(Key, Plataforma);
                MapPlat.Add(Plataforma);
                Posicion.Y -= PosicionAuxiliar;
                Posicion.Z -= 70.f;
            }
            Posicion.Z += 150.f;
            Posicion.Z += 1100.0f;
            Posicion.Y *= (-1);
        }
    }
    do {
        aux1 = FMath::RandRange(1, 8);
        aux2 = FMath::RandRange(21, 28);
        aux3 = FMath::RandRange(31, 38);
    } while (aux1 == aux2 || aux1 == aux3 || aux2 == aux3);
    
    /*
    FString Key1 = FString::Printf(TEXT("Plataforma%d"), aux1);
    FString Key2 = FString::Printf(TEXT("Plataforma%d"), aux2);
    FString Key3 = FString::Printf(TEXT("Plataforma%d"), aux3);
    */
    
    /*
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
    */
    if (MapPlat.IsValidIndex(aux1)) {
        APlataformas* Plataforma1 = Cast<APlataformas>(MapPlat[aux1]);
        if (Plataforma1) {
            Plataforma1->setmover(true);
            Plataforma1->setdireccion(1);
            if (GEngine) {
                GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Plataforma %d se está moviendo"), aux1));
            }
            APlataformas* PlataformaAnterior1 = Cast<APlataformas>(MapPlat[aux1 - 1]);
            if (PlataformaAnterior1) {
                PlataformaAnterior1->Destroy();
            }

            APlataformas* PlataformaSiguiente1 = Cast<APlataformas>(MapPlat[aux1 + 1]);
            if (PlataformaSiguiente1) {
                PlataformaSiguiente1->Destroy();
            }
        }
    }
    if (MapPlat.IsValidIndex(aux2)) {
        APlataformas* Plataforma2 = Cast<APlataformas>(MapPlat[aux2]);
        if (Plataforma2) {
            Plataforma2->setmover(true);
            Plataforma2->setdireccion(2);
            if (GEngine) {
                GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Plataforma %d se está moviendo"), aux2));
            }
            APlataformas* PlataformaAnterior2 = Cast<APlataformas>(MapPlat[aux2 - 1]);
            if (PlataformaAnterior2) {
                PlataformaAnterior2->Destroy();
            }

            APlataformas* PlataformaSiguiente2 = Cast<APlataformas>(MapPlat[aux2 + 1]);
            if (PlataformaSiguiente2) {
                PlataformaSiguiente2->Destroy();
            }
        }
    }
    if (MapPlat.IsValidIndex(aux3)) {
        APlataformas* Plataforma3 = Cast<APlataformas>(MapPlat[aux3]);
        if (Plataforma3) {
            Plataforma3->setmover(true);
            Plataforma3->setdireccion(1);
            if (GEngine) {
                GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Plataforma %d se está moviendo"), aux3));
            }
            APlataformas* PlataformaAnterior3 = Cast<APlataformas>(MapPlat[aux3 - 1]);
            if (PlataformaAnterior3) {
                PlataformaAnterior3->Destroy();
            }

            APlataformas* PlataformaSiguiente3 = Cast<APlataformas>(MapPlat[aux3 + 1]);
            if (PlataformaSiguiente3) {
                PlataformaSiguiente3->Destroy();
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
        //FString Key = FString::Printf(TEXT("Plataforma%d"), PlataformaIndex);
        /*
        if (MapPlat.Contains(Key))
        {
            APlataformas* Plataforma = Cast<APlataformas>(MapPlat[Key]);
            if (Plataforma)
            {
                FVector MuroPosicion = Plataforma->GetActorLocation() + FVector(0, 200, 250);
                if(EnemigosGenerados==0)
                    AMuro* Muro = GetWorld()->SpawnActor<AMuro>(AMuroElectrico::StaticClass(), MuroPosicion, FRotator::ZeroRotator);
               if (EnemigosGenerados == 1)
                    AMuro* Muro = GetWorld()->SpawnActor<AMuro>(AMuroLadrillo::StaticClass(), MuroPosicion, FRotator::ZeroRotator);
               if (EnemigosGenerados == 2)
                    AMuro* Muro = GetWorld()->SpawnActor<AMuro>(AMuroPegajoso::StaticClass(), MuroPosicion, FRotator::ZeroRotator);
               if (EnemigosGenerados == 3)
                    AMuro* Muro = GetWorld()->SpawnActor<AMuro>(AMuroCongelado::StaticClass(), MuroPosicion, FRotator::ZeroRotator);
                FVector EnemigoPosicion = Plataforma->GetActorLocation() + FVector(0, 0, 200);
                AEnemigoDisparo* Enemigo = GetWorld()->SpawnActor<AEnemigoDisparo>(EnemigoClase, EnemigoPosicion, FRotator::ZeroRotator); 
                 Enemigos.Add(Enemigo);
                    EnemigosGenerados++;
            }
        }
        */
        if (MapPlat.IsValidIndex(PlataformaIndex))
        {
            APlataformas* Plataforma = Cast<APlataformas>(MapPlat[PlataformaIndex]);
            if (Plataforma)
            {
                FVector MuroPosicion = Plataforma->GetActorLocation() + FVector(0, 200, 250);
                if (EnemigosGenerados == 0)
                    AMuro* Muro = GetWorld()->SpawnActor<AMuro>(AMuroElectrico::StaticClass(), MuroPosicion, FRotator::ZeroRotator);
                if (EnemigosGenerados == 1)
                    AMuro* Muro = GetWorld()->SpawnActor<AMuro>(AMuroLadrillo::StaticClass(), MuroPosicion, FRotator::ZeroRotator);
                if (EnemigosGenerados == 2)
                    AMuro* Muro = GetWorld()->SpawnActor<AMuro>(AMuroPegajoso::StaticClass(), MuroPosicion, FRotator::ZeroRotator);
                if (EnemigosGenerados == 3)
                    AMuro* Muro = GetWorld()->SpawnActor<AMuro>(AMuroCongelado::StaticClass(), MuroPosicion, FRotator::ZeroRotator);
                if(EnemigosGenerados == 4)
                    AMuro* Muro = GetWorld()->SpawnActor<AMuro>(AMuroEspejo::StaticClass(), MuroPosicion, FRotator::ZeroRotator);
                if (EnemigosGenerados == 3) {
                    FVector EnemigoPosicion = MapPlat[24]->GetActorLocation() + FVector(0, 0, 400);
                    AEnemigoDisparo* Enemigo = GetWorld()->SpawnActor<AEnemigoDisparo>(EnemigoClase, EnemigoPosicion, FRotator::ZeroRotator);
                    Enemigos.Add(Enemigo);
                }
                EnemigosGenerados++;
            }
        }
    }
}
