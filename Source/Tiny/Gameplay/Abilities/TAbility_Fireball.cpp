// Fill out your copyright notice in the Description page of Project Settings.


#include "TAbility_Fireball.h"

#include "Tiny/TCharacter.h"
#include "Tiny/Gameplay/TAbilityTask.h"
#include "Tiny/Gameplay/AbilityTasks/TAbilityTask_PlayActionAndWaitForEvent.h"
#include "Tiny/Gameplay/AbilityTasks/TAbilityTask_SpawnActorAndWaitForEvent.h"

void UTAbility_Fireball::ActivateAbility()
{
	Super::ActivateAbility();

	//Ability Data
	FTAbilityTaskData ActionTaskParams;
	ActionTaskParams.AddField<FString>("Event", "Fireball");
	ActionTaskParams.AddField<FString>("Montage", "Fireball");
	FTAbilityTaskData FireballTaskParams;
	FireballTaskParams.AddField<FString>("Event", "Hit");
	// FireballTaskParams.AddField<FVector>("TargetInfo", );
	FireballTaskParams.AddField<uint32>("Damage", 35);

	//Ability Flow 
	ExecuteTask(UTAbilityTask_PlayActionAndWaitForEvent::StaticClass(), ActionTaskParams);
	ExecuteTask(UTAbilityTask_SpawnActorAndWaitForEvent::StaticClass(), FireballTaskParams);
	if(FireballTaskParams.GetField("Event"))
	{
		// auto TChar = Cast<ATCharacter>(FireballTaskParams.GetField("HitChar"));
	}
	EndAbility();
}

void UTAbility_Fireball::EndAbility()
{
	Super::EndAbility();
}
