// Fill out your copyright notice in the Description page of Project Settings.


#include "TAbilityTask.h"

void UTAbilityTask::EndTask()
{
	OnEndTask.Broadcast(this);
}

void UTAbilityTask::OnExecuteTask(UObject* OwningObject)
{
}

void UTAbilityTask::InitTaskFromData(const FTAbilityTaskData& Data)
{
	TaskData = Data;
}
