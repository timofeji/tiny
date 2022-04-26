// Fill out your copyright notice in the Description page of Project Settings.


#include "TAbility.h"

#include "Tiny/TGameplayGlobals.h"

void UTAbility::ActivateAbility()
{
	ensureAlwaysMsgf(TOwner, TEXT("%s(): tried to activate ability without an owner"),*FString
	(__FUNCTION__) );

}

void UTAbility::EndAbility()
{
	BeginDestroy();

	//Remove all remaining tasks active tasks
	for(auto Task : ActiveTasks)
	{
		Task->EndTask();
		Task->BeginDestroy();
	}
}

void UTAbility::ExecuteTask(TSubclassOf<UTAbilityTask>AbilityClass, FTAbilityTaskData& Data)
{
	UTAbilityTask* Task = NewObject<UTAbilityTask>(this, AbilityClass);
	ActiveTasks.Add(Task);
	// UTGameplayGlobals::EmitEvent(FString::Format(""));
}

void UTAbility::BindAbilityToCharacter(UObject* Owner)
{
	TOwner = Owner;
}
