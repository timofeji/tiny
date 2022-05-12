// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TAbilityTask.h"
#include "Components/HorizontalBox.h"
#include "Tiny/TTypes.h"
#include "Tiny/UI/THudWidget.h"
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


DECLARE_MULTICAST_DELEGATE_OneParam(FAbilityActivated,
                                    FActivationData&);
DECLARE_MULTICAST_DELEGATE(FAbilityEnded);
DECLARE_MULTICAST_DELEGATE(FAbilityCommitted);


/**
 * 
 */
UCLASS(Blueprintable)
class TINY_API UTAbility : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UTAbility();

	UPROPERTY(EditAnywhere)
	bool bShouldActivateOnInput;
	
	UPROPERTY(EditAnywhere)
	UTexture2D* AbilityIcon;

	bool bIsPendingExecution = false;

	float CoolDown = 0.4f;
	bool bIsExecuting = false;
	bool bIsPredicted = true;


	UFUNCTION(BlueprintCallable)
	virtual void ActivateAbility();

	UFUNCTION(BlueprintImplementableEvent)
	void AbilityTick(float DeltaTime);

	UFUNCTION(BlueprintImplementableEvent)
	void OnActivateAbility();

	void ExecuteTaskFlow();

	//Consume cooldown
	UFUNCTION(BlueprintCallable)
	void CommitAbility();

	bool ShouldExecuteFlow();

	UFUNCTION(BlueprintCallable)
	virtual void EndAbility();

	void ActivateTask(UTAbilityTask* Task);
	void OnTaskEnded(UTAbilityTask* Task);


	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;


	UFUNCTION(BlueprintCallable)
	void AddExecutionTask(TSubclassOf<UTAbilityTask> TaskClass, FTAbilityTaskData Data);

	void BindAbilityToCharacter(UObject* Owner);

	UFUNCTION(BlueprintCallable,
		BlueprintImplementableEvent)
	void OnInputReleased();
	virtual void InputReleased() { OnInputReleased(); }


	UFUNCTION(BlueprintCallable,
		BlueprintImplementableEvent)
	void OnInputPressed();

	

	virtual void InputPressed() { OnInputPressed();}
	
	bool HasTag(FString Tag);

	FAbilityActivated OnAbilityActivated;

	FAbilityEnded OnAbilityEnded;
	FAbilityCommitted OnAbilityCommitted;


	TArray<UTAbilityTask*> ActiveTasks;

	TArray<UTAbilityTask*> PendingTasks;

	UTAbilityTask* CurrentlyExecutingTask;

	FORCEINLINE UObject* GetOwner() { return TOwner; }

protected:
	UObject* TOwner;
};
