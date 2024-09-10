// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlataformasSpawnGameMode.h"
#include "PlataformasSpawnCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Plataformas.h"
#include "Barril.h"

APlataformasSpawnGameMode::APlataformasSpawnGameMode()
{

	PrimaryActorTick.bCanEverTick = true;
	FMath::RandInit(FDateTime::Now().GetMillisecond());
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	Posicion = FVector(1180.f, 1100.f, 140.f);
	Rotacion = FRotator(0.0f,0.0f,0.0f);
	PosicionAuxiliar = 750.f;
	Time = 0.0f;
	spawnsPlataformas = 0;
	band = 0;
	cont = -1;
	
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
				MapPlat.Add(cont++, Plataforma);
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
                MapPlat.Add(cont++, Plataforma);
				Posicion.Y -= PosicionAuxiliar;
				Posicion.Z -= 80.f;
			}
			Posicion.Z += 240.f;
			Posicion.Z += 600.0f;
			Posicion.Y *= (-1);
		}
	}
	aux1 = FMath::RandRange(0, MapPlat.Num() - 1);
	aux2 = FMath::RandRange(0, MapPlat.Num() - 1);
	aux3 = FMath::RandRange(0, MapPlat.Num() - 1);

	if (APlataformas* Plataforma = Cast<APlataformas>(MapPlat[aux1]))
         Plataforma->setmover(true);
    if (APlataformas* Plataforma = Cast<APlataformas>(MapPlat[aux2]))
         Plataforma->setmover(true);
    if (APlataformas* Plataforma = Cast<APlataformas>(MapPlat[aux3]))
         Plataforma->setmover(true);
}
	//spawnsPlataformas = ContPlataformas.Num() - 1; //4 elementos [0,1,2,3]
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, 
		//FString::Printf(TEXT("Cantidad del contenedor: %d"), ContPlataformas.Num()));

	//Ba = GetWorld()->SpawnActor<ABarril>(ABarril::StaticClass(), FVector(1210.f, 970.f, 1900.f), FRotator::ZeroRotator);


void APlataformasSpawnGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Time += DeltaTime;

	//Codigo para eliminar plataformas con un reloj.
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
		//FString::Printf(TEXT("Cantidad del contenedor: %d"), ContPlataformas.Num()));

	//if (Time > 3.0f) {
		//if (spawnsPlataformas != -1) {
			//AActor* plataforma = ContPlataformas[spawnsPlataformas];
			//plataforma->Destroy();
			//ContPlataformas.RemoveAt(ContPlataformas.Num() - 1);
		//if (contba<5) {
			//Ba = GetWorld()->SpawnActor<ABarril>(ABarril::StaticClass(), FVector(1210.f, 970.f, 1900.f), FRotator::ZeroRotator);
		//}
		//Time = 0.f;
		//contba++;
			//spawnsPlataformas -= 1;
		//}
		
	//}
	
}
