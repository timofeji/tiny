// Fill out your copyright notice in the Description page of Project Settings.


#include "TPlayerController.h"

#include "TCheatManager.h"


// Sets default values
ATPlayerController::ATPlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CheatClass = UTCheatManager::StaticClass();
}

// Called when the game starts or when spawned
void ATPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

