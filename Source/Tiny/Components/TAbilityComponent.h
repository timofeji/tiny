// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Tiny/TCharacter.h"
#include "TAbilityComponent.generated.h"


class UTAbility;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilityBound, UTAbility* )


UCLASS(ClassGroup=(Custom),
	meta=(BlueprintSpawnableComponent))
class TINY_API UTAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTAbilityComponent();

	TArray<UTAbility*> OwnedAbilities;

	
	FOnAbilityBound OnAbilityBound;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
	UInputComponent* PlayerInputComponent;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	void AddAbility(const TSubclassOf<UTAbility>& Class);
	
	void ActivateAbility(const int32 AbilityIndex);
	
	void SetupInput(UInputComponent* InputComponent);
	
	void BindAbility(TTuple<TEnumAsByte<ETCharacterInputAction>, TSubclassOf<UTAbility>> AbilityBind);
};
