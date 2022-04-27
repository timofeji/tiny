// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tiny/Gameplay/TAbilityTask.h"
#include "UObject/Object.h"
#include "TAbilityTask_PlayActionAndWaitForEvent.generated.h"

/**
 * 
 */
UCLASS()
class TINY_API UTAbilityTask_PlayActionAndWaitForEvent : public UTAbilityTask
{
	GENERATED_BODY()

	virtual void OnExecuteTask(UObject* OwningObject) override;
};
