// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Tiny/TCharacter.h"
#include "TAbilitySystemComponent.generated.h"


class UTAbility;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilityBound, UTAbility* )
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilityRemoved, UTAbility* )


UCLASS(ClassGroup=(Custom),
	meta=(BlueprintSpawnableComponent))
class TINY_API UTAbilitySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTAbilitySystemComponent();
	
	UPROPERTY(EditAnywhere, Category=Gameplay)
	TMap<TEnumAsByte<ETCharacterInputAction>, TSubclassOf<UTAbility>> DefaultAbilities;

	TArray<UTAbility*> OwnedAbilities;

	
	FOnAbilityBound OnAbilityBound;
	
	FOnAbilityRemoved OnAbilityRemoved;
	
	TArray<uint8> InputQueue;
protected:

	virtual void PostInitProperties() override;
	
	TMap<ETCharacterInputAction, UTAbility*> AbilityBinds;

	
	UInputComponent* PlayerInputComponent;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	void AddAbility(const TSubclassOf<UTAbility>& Class);
	
	void ActivateAbility(const int32 AbilityIndex);
	
	void SetupDefaultInput(UInputComponent* InputComponent);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerAbilityInputPressed(ETCharacterInputAction AbilitInputIndex);
	
	
	void AbilityInputPressed(ETCharacterInputAction AbilityInputIndex);
	
	void AbilityInputReleased(ETCharacterInputAction AbilityInput);

	void BindAbility(TTuple<ETCharacterInputAction, TSubclassOf<UTAbility>> AbilityBind);
	
	void BindDefaultAbilities();
	
};
