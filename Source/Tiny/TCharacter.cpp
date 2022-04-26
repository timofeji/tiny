// Fill out your copyright notice in the Description page of Project Settings.


#include "TCharacter.h"

#include "Components/TAbilityComponent.h"

// Sets default values
ATCharacter::ATCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	AbilityComponent = CreateDefaultSubobject<UTAbilityComponent>(
		TEXT("Ability Component"));
	if (ensureAlwaysMsgf(AbilityComponent,
	                     TEXT("TAbilitySystem not initialized properly")))
	{
		for (auto Ability : DefaultAbilities)
		{
			AbilityComponent->AddAbility(Ability);
		}
	}
}

void ATCharacter::RegisterDefaultAbilities()
{
}

// Called when the game starts or when spawned
void ATCharacter::BeginPlay()
{
	Super::BeginPlay();


	RegisterDefaultAbilities();
}

// Called every frame
void ATCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
