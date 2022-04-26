// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TGameplayGlobals.generated.h"

/**
 * 
 */
UCLASS()
class TINY_API UTGameplayGlobals : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static void EmitGameplayEvent();
};
