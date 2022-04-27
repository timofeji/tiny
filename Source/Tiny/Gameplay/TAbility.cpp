// Fill out your copyright notice in the Description page of Project Settings.


#include "TAbility.h"

#include "Kismet/GameplayStatics.h"
#include "Tiny/TGameplayGlobals.h"

void UTAbility::ActivateAbility()
{
	if(bIsPendingActivation)
	{
		return;
	}

	
	ensureAlwaysMsgf(TOwner,
	                 TEXT("%s(): tried to activate ability without an owner"),
	                 *FString
	                 (__FUNCTION__));

	OnActivateAbility();
}

void UTAbility::EndAbility()
{
	//Remove all remaining tasks active tasks
	for (auto Task : ActiveTasks)
	{
		Task->EndTask();
		Task->BeginDestroy();
	}
}

void UTAbility::ActivateTask(UTAbilityTask* Task)
{
	Task->OnExecuteTask(TOwner);
	// Task->OnEndTask.Add();
	CurrentlyExecutingTask = Task;
}

void UTAbility::EndTask(UTAbilityTask* Task)
{
	if (Task == CurrentlyExecutingTask)
	{
		CurrentlyExecutingTask = nullptr;
	}

	UTAbilityTask* NewTaskToActivate;
	TaskQueue.Dequeue(NewTaskToActivate);

	if (NewTaskToActivate)
	{
		ActivateTask(NewTaskToActivate);
	}
}


void UTAbility::ExecuteTask(TSubclassOf<UTAbilityTask> TaskClass, FTAbilityTaskData Data)
{
	if (!TaskClass)
	{
		return;
	}
	UTAbilityTask* Task = NewObject<UTAbilityTask>(GetOuter(),
	                                               TaskClass, NAME_None, RF_StrongRefOnFrame);
	Task->InitTaskFromData(Data);


	ActiveTasks.Add(Task);

	//If we're currently performing a task que task, otherwise activate it
	if (CurrentlyExecutingTask)
	{
		TaskQueue.Enqueue(Task);
	}
	else
	{
		ActivateTask(Task);
	}
}

void UTAbility::BindAbilityToCharacter(UObject* Owner)
{
	TOwner = Owner;
}
