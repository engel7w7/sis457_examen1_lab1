// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AdaptadorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAdaptadorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLATAFORMASSPAWN_API IAdaptadorInterface
{
	GENERATED_BODY()
public:
	virtual void cargar() PURE_VIRTUAL(IAdaptadorInterface::cargar();)// 1.- implementamos una funcion virtual paraa acceder a todas las clases
};
