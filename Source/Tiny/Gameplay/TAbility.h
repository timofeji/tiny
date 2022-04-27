// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TAbilityTask.h"
#include "Tiny/TTypes.h"
#include "UObject/Object.h"
#include "TAbility.generated.h"

class UTexture2D;
class UTAbilityTask;
/**
 * 
 */
UCLASS(Blueprintable)
class TINY_API UTAbility : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UTexture2D* AbilityIcon;

	UFUNCTION(BlueprintCallable)
	virtual void ActivateAbility();

	UFUNCTION(BlueprintImplementableEvent)
	void OnActivateAbility();

	UFUNCTION(BlueprintCallable)
	virtual void EndAbility();

	void ActivateTask(UTAbilityTask* Task);
	void EndTask(UTAbilityTask* Task);

	
	UFUNCTION(BlueprintCallable)
	void ExecuteTask(TSubclassOf<UTAbilityTask> TaskClass, FTAbilityTaskData Data);

	void BindAbilityToCharacter(UObject* Owner);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void OnInputReleased();
	virtual void InputReleased() { OnInputReleased(); }


	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void OnInputPressed();
	virtual void InputPressed() { OnInputPressed(); }


	TArray<UTAbilityTask*> ActiveTasks;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ETCharacterInputAction> ActivationInputIndex;
	TQueue<UTAbilityTask*> TaskQueue;

	UTAbilityTask* CurrentlyExecutingTask;

	FORCEINLINE UObject* GetOwner() { return TOwner; }

protected:
	UObject* TOwner;
};
