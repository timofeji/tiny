// Fill out your copyright notice in the Description page of Project Settings.


#include "TAbilityTask.h"

void UTAbilityTask::EndTask()
{
	OnEndTask.Broadcast();
}

void UTAbilityTask::OnExecuteTask(UObject* OwningObject)
{
}

void UTAbilityTask::InitTaskFromData(const FTAbilityTaskData& Data)
{
	TaskData = Data;
}
