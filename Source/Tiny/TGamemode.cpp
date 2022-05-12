// Fill out your copyright notice in the Description page of Project Settings.


#include "TGamemode.h"
#include "TCharacter.h"
#include "Components/TAbilitySystemComponent.h"


// Sets default values
ATGamemode::ATGamemode()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATGamemode::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATGamemode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATGamemode::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);
	
	auto TChar = Cast<ATCharacter>(NewPlayer->GetPawn());
	if(!IsValid(TChar))
	{
		return;
	}
}

