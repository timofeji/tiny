// Fill out your copyright notice in the Description page of Project Settings.


#include "TAbility_Fireball.h"

#include "Tiny/TCharacter.h"
#include "Tiny/Gameplay/TAbilityTask.h"
#include "Tiny/Gameplay/AbilityTasks/TAbilityTask_PlayActionAndWaitForEvent.h"
#include "Tiny/Gameplay/AbilityTasks/TAbilityTask_SpawnActorAndWaitForEvent.h"

UTAbility_Fireball::UTAbility_Fireball()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UTexture2D> Icon;

		FConstructorStatics()
			: Icon(
				TEXT("Texture2D'/Game/UI/IconTextures/T_UI_Fireball.T_UI_Fireball'"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	AbilityIcon = ConstructorStatics.Icon.Object;
}

void UTAbility_Fireball::ActivateAbility()
{
	Super::ActivateAbility();

	//Ability Data
	FTAbilityTaskData ActionTaskParams;
	ActionTaskParams.AddField<FString>("Event",
	                                   "Fireball");
	ActionTaskParams.AddField<FString>("Montage",
	                                   "Fireball");
	FTAbilityTaskData FireballTaskParams;
	FireballTaskParams.AddField<FString>("Event",
	                                     "Hit");
	// FireballTaskParams.AddField<FVector>("TargetInfo", );
	FireballTaskParams.AddField<uint32>("Damage",
	                                    35);

	//Ability Flow
	AddTask(UTAbilityTask_SpawnActorAndWaitForEvent::StaticClass(),
	                       FireballTaskParams);

	AddTask(UTAbilityTask_PlayActionAndWaitForEvent::StaticClass(),
	                       ActionTaskParams);

	EndAbility();
}

void UTAbility_Fireball::EndAbility()
{
	Super::EndAbility();
}

void UTAbility_Fireball::InputPressed()
{
	Super::InputPressed();

	ActivateAbility();
}
