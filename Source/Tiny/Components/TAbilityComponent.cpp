// Fill out your copyright notice in the Description page of Project Settings.


#include "TAbilityComponent.h"
#include "Tiny/Gameplay/TAbility.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UTAbilityComponent::UTAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,
	                     TickType,
	                     ThisTickFunction);

	// ...
}

void UTAbilityComponent::AddAbility(const TSubclassOf<UTAbility>& Class)
{
	if(GetOwnerRole() < ROLE_Authority)
	{
		return;
	}
	
	UTAbility* NewAbility = NewObject<UTAbility>(GetOuter(), Class);
	NewAbility->BindAbilityToCharacter(GetOuter());
	ActiveAbilities.Add(NewAbility);
}

