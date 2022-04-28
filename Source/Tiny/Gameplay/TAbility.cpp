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

	FActivationData ActivationData;

	OnActivateAbility();
	OnAbilityActivated.Broadcast(ActivationData);
}

void UTAbility::ExecuteTaskFlow()
{
	
}

bool UTAbility::ShouldExecuteFlow()
{
	return bIsPendingActivation || PendingTasks.Num() > 0;
}

void UTAbility::EndAbility()
{
	if(ShouldExecuteFlow())
	{
		ExecuteTaskFlow();
	}
	
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
}

//Queues up an ability task into the execution flow
void UTAbility::AddTask(TSubclassOf<UTAbilityTask> TaskClass, FTAbilityTaskData Data)
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
