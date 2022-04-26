// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TAbilityTask.h"
#include "UObject/Object.h"
#include "TAbility.generated.h"


class UTAbilityTask;
/**
 * 
 */
UCLASS(Blueprintable)
class TINY_API UTAbility : public UObject
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility();

	virtual void EndAbility();

	UFUNCTION(BlueprintCallable)
	void ExecuteTask(TSubclassOf<UTAbilityTask> AbilityClass, FTAbilityTaskData& Data);

	void BindAbilityToCharacter(UObject* Owner);

	TArray<UTAbilityTask*> ActiveTasks;

	FORCEINLINE UObject* GetOwner() { return TOwner; }

protected:
	UObject* TOwner;
};
