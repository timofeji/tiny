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
		ConstructorHelpers::FObjectFinder<UAnimMontage> Montage;

		FConstructorStatics()
			: Icon(
				TEXT("Texture2D'/Game/UI/IconTextures/T_UI_Fireball.T_UI_Fireball'")),
			Montage(
				TEXT("AnimMontage'/Game/Characters/Mannequins/Meshes/AM_Fireball.AM_Fireball'"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	AbilityIcon = ConstructorStatics.Icon.Object;
	FireballMontage = ConstructorStatics.Montage.Object;
}

void UTAbility_Fireball::ActivateAbility()
{
	Super::ActivateAbility();


	//Ability Data
	FTAbilityTaskData ActionTaskParams;
	ActionTaskParams.AddField<FString>("Event",
	                                   "Fireball");
	ActionTaskParams.AddField<UAnimMontage>("Montage",
	                                        FireballMontage);
	FTAbilityTaskData FireballTaskParams;
	FireballTaskParams.AddField<FString>("Event",
	                                     "Hit");
	// FireballTaskParams.AddField<FVector>("TargetInfo", );

	FireballTaskParams.AddField<uint32>(FName("Damage"),
	                                    &Damage);

	//Ability Flow
	AddExecutionTask(UTAbilityTask_SpawnActorAndWaitForEvent::StaticClass(),
	                 FireballTaskParams);

	AddExecutionTask(UTAbilityTask_PlayActionAndWaitForEvent::StaticClass(),
	                 ActionTaskParams);

	CommitAbility();

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
