// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tiny/Gameplay/TAbility.h"
#include "UObject/Object.h"
#include "TAbility_Fireball.generated.h"



DECLARE_EVENT( UTAbility_Fireball, HitEvent )

/**
 * C++ Ability Example
 */
UCLASS()
class TINY_API UTAbility_Fireball : public UTAbility
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility() override;

	virtual void EndAbility() override;

};
