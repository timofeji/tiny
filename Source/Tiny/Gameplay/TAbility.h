// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TAbilityTask.h"
#include "Tiny/TTypes.h"
#include "UObject/Object.h"
#include "TAbility.generated.h"

class UTexture2D;
class UTAbilityTask;


USTRUCT()
struct FActivationData
{
	GENERATED_BODY()

	float Cooldown;
};


DECLARE_MULTICAST_DELEGATE_OneParam(FAbilityActivated, FActivationData&);
DECLARE_MULTICAST_DELEGATE(FAbilityEnded);
DECLARE_MULTICAST_DELEGATE(FAbilityCommitted);



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
	
	bool bIsPendingActivation = false;
	

	UFUNCTION(BlueprintCallable)
	virtual void ActivateAbility();

	UFUNCTION(BlueprintImplementableEvent)
	void OnActivateAbility();

	void ExecuteTaskFlow();
	
	void CommitAbility();

	bool ShouldExecuteFlow();
	
	UFUNCTION(BlueprintCallable)
	virtual void EndAbility();

	void ActivateTask(UTAbilityTask* Task);
	void OnTaskEnded(UTAbilityTask* Task);

	
	UFUNCTION(BlueprintCallable)
	void AddExecutionTask(TSubclassOf<UTAbilityTask> TaskClass, FTAbilityTaskData Data);

	void BindAbilityToCharacter(UObject* Owner);

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void OnInputReleased();
	virtual void InputReleased() { OnInputReleased(); }


	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void OnInputPressed();
	virtual void InputPressed() { OnInputPressed(); }

	FAbilityActivated OnAbilityActivated;
	
	FAbilityEnded OnAbilityEnded;
	FAbilityCommitted OnAbilityCommitted;


	TArray<UTAbilityTask*> ActiveTasks;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ETCharacterInputAction> ActivationInputIndex;
	TArray<UTAbilityTask*> PendingTasks;

	UTAbilityTask* CurrentlyExecutingTask;

	FORCEINLINE UObject* GetOwner() { return TOwner; }

protected:
	UObject* TOwner;
};
