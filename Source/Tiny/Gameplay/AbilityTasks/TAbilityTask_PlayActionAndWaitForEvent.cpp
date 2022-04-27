// Fill out your copyright notice in the Description page of Project Settings.


#include "TAbilityTask_PlayActionAndWaitForEvent.h"

#include "Tiny/TCharacter.h"

void UTAbilityTask_PlayActionAndWaitForEvent::OnExecuteTask(UObject* OwningObject)
{
	auto TChar = Cast<ATCharacter>(OwningObject);
	// TaskData.GetField()
	// TChar->PlayAnimMontage();
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("LOCATION:")));
}
