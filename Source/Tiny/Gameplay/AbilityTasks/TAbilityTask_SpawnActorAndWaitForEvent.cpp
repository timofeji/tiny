// Fill out your copyright notice in the Description page of Project Settings.


#include "TAbilityTask_SpawnActorAndWaitForEvent.h"

void UTAbilityTask_SpawnActorAndWaitForEvent::OnExecuteTask(UObject* OwningObject)
{
	Super::OnExecuteTask(OwningObject);

	auto Damage = *TaskData.GetField<int32>(FName("Damage"));
	GEngine->AddOnScreenDebugMessage(-1,
	                                 5.0f,
	                                 FColor::Red,
	                                 FString::Printf(TEXT("Damage :%i"), Damage));
	EndTask();
}
