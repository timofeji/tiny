// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPlayerController.generated.h"

class ATCharacter;

UCLASS()
class TINY_API ATPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	ATCharacter* TChar;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ClientRestart_Implementation(APawn* NewPawn) override;
};
