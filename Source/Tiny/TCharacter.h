// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TCharacter.generated.h"


UENUM()
enum ETCharacterInputAction
{
	Attack,
	Spell,
	
};

class UTAbilityComponent;
class UTAbility;

UCLASS()
class TINY_API ATCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATCharacter();

	UTAbilityComponent* AbilityComponent;

	UPROPERTY(EditDefaultsOnly, Category=Gameplay)
	TArray<TSubclassOf<UTAbility>> DefaultAbilities;

protected:
	void RegisterDefaultAbilities();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
