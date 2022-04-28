// Fill out your copyright notice in the Description page of Project Settings.


#include "TAbilityTask_PlayActionAndWaitForEvent.h"

#include "Tiny/TCharacter.h"
#include "Tiny/TGameplayGlobals.h"

void UTAbilityTask_PlayActionAndWaitForEvent::OnExecuteTask(UObject* OwningObject)
{
	const auto Montage = TaskData.GetField<UAnimMontage>("Montage");
	const auto TChar = Cast<ATCharacter>(OwningObject);
	TChar->PlayAnimMontage(Montage);
	// UTGameplayGlobals::Bind
	EndTask();
}
