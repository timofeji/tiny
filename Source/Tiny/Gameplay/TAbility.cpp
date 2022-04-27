// Fill out your copyright notice in the Description page of Project Settings.


#include "TAbility.h"

#include "Kismet/GameplayStatics.h"
#include "Tiny/TGameplayGlobals.h"

void UTAbility::ActivateAbility()
{
	if (bIsPendingActivation)
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
	Task->OnEndTask.AddUObject(this,
	                       &UTAbility::OnTaskEnded);
	
	CurrentlyExecutingTask = Task;
	Task->OnExecuteTask(TOwner);
}

//Check if newly ended task is the currently executing one,
//and execute the next one in the queue
void UTAbility::OnTaskEnded(UTAbilityTask* Task)
{
	Task->BeginDestroy();
	
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
	                                               TaskClass,
	                                               NAME_None,
	                                               RF_StrongRefOnFrame);
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
