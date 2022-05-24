// Fill out your copyright notice in the Description page of Project Settings.


#include "TAbility.h"

#include "Kismet/GameplayStatics.h"
#include "Tiny/TGameplayGlobals.h"

UTAbility::UTAbility()
{
}

void UTAbility::ActivateAbility()
{
	if (bIsPendingExecution || CoolDown > 0 )
	{
		return;
	}
	
	ensureAlwaysMsgf(TOwner,
	                 TEXT("%s(): tried to activate ability without an owner"),
	                 *FString
	                 (__FUNCTION__));

	FActivationData ActivationData;
	ActivationData.Cooldown = 3.f;
	CoolDown = 3.f;

	OnActivateAbility();
	OnAbilityActivated.Broadcast(ActivationData);

	bIsPendingExecution = true;
}

void UTAbility::ExecuteTaskFlow()
{
	bIsExecuting = true;
	// auto NextTask = PendingTasks.Pop();
	
}

void UTAbility::CommitAbility()
{
	OnAbilityCommitted.Broadcast();
	ExecuteTaskFlow();
}

bool UTAbility::ShouldExecuteFlow()
{
	return bIsPendingExecution || PendingTasks.Num() > 0;
}

void UTAbility::EndAbility()
{
	bIsExecuting = true;
	
	OnAbilityEnded.Broadcast();
}

void UTAbility::ActivateTask(UTAbilityTask* Task)
{
	Task->OnEndTask.AddUObject(this,
	                           &UTAbility::OnTaskEnded);

	CurrentlyExecutingTask = Task;
	Task->OnExecuteTask(TOwner);
}

//Check if newly ended task is the currently executing one,
//and execute the next one in the queue
void UTAbility::OnTaskEnded(UTAbilityTask* Task)
{
	if (PendingTasks.Num() > 0)
	{
		UTAbilityTask* NewTaskToActivate = PendingTasks.Pop(true);

		if (NewTaskToActivate)
		{
			ActivateTask(NewTaskToActivate);
		}
	}
	
	bIsExecuting = false;
}

void UTAbility::Tick(float DeltaTime)
{
	AbilityTick(DeltaTime);

	if(CoolDown > 0)
	{
		CoolDown -= DeltaTime;
	}
}

bool UTAbility::IsTickable() const
{
	return bIsExecuting;
}

TStatId UTAbility::GetStatId() const
{
	return UObject::GetStatID();
}

//Queues up an ability task into the execution flow
void UTAbility::AddExecutionTask(TSubclassOf<UTAbilityTask> TaskClass, FTAbilityTaskData Data)
{
	if (!TaskClass)
	{
		return;
	}
	UTAbilityTask* Task = NewObject<UTAbilityTask>(GetOuter(),
	                                               TaskClass,
	                                               NAME_None,
	                                               RF_StrongRefOnFrame);
	Task->InitTaskFromData(Data);
	PendingTasks.Add(Task);
}

void UTAbility::BindAbilityToCharacter(UObject* Owner)
{
	TOwner = Owner;
}

bool UTAbility::HasTag(FString Tag)
{
	return false;
}
