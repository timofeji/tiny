// Fill out your copyright notice in the Description page of Project Settings.


#include "TAbilitySystemComponent.h"
#include "Tiny/Gameplay/TAbility.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UTAbilitySystemComponent::UTAbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}

void UTAbilitySystemComponent::PostInitProperties()
{
	Super::PostInitProperties();
	

}


// Called every frame
void UTAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,
	                     TickType,
	                     ThisTickFunction);

	// ...
}

void UTAbilitySystemComponent::AddAbility(const TSubclassOf<UTAbility>& Class)
{
}

void UTAbilitySystemComponent::ActivateAbility(const int32 AbilityIndex)
{
	UE_LOG(LogTemp,
	       Display,
	       TEXT("Attempting to activate ability index:%i"),
	       AbilityIndex);
}

void UTAbilitySystemComponent::SetupDefaultInput(UInputComponent* InputComponent)
{
	ensureAlways(InputComponent);
	PlayerInputComponent = InputComponent;

	if(AbilityBinds.Num() > 0)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ETCharacterInputAction"), true);
		for(auto AbilityBind :AbilityBinds)
		{
			auto BindName = EnumPtr->GetNameStringByIndex((int32)AbilityBind.Key);
			
			// Bind the press event.
			FInputActionBinding PressedAB( *BindName, IE_Pressed );
			PressedAB.ActionDelegate.GetDelegateForManualSet().BindLambda(
				[this, AbilityBind]() { AbilityInputPressed( AbilityBind.Key ); }
			);
			InputComponent->AddActionBinding( PressedAB );
			
			// Bind the release event.
			FInputActionBinding ReleasedAB( *BindName, IE_Released );
			ReleasedAB.ActionDelegate.GetDelegateForManualSet().BindLambda(
				[this, AbilityBind]() { AbilityInputReleased( AbilityBind.Key ); }
			);
			InputComponent->AddActionBinding( ReleasedAB );
		
			OnAbilityBound.Broadcast(AbilityBind.Value);
		}
	}
}

void UTAbilitySystemComponent::AbilityInputPressed(ETCharacterInputAction AbilityInputIndex)
{
	if(GetOwnerRole() < ROLE_Authority)
	{
		ServerAbilityInputPressed(AbilityInputIndex);
	}

	if(!AbilityBinds.Contains(AbilityInputIndex))
	{
		return;
	}
	
	//If Ability not locally predicted we want to skip local input execution
	UTAbility* Ability = AbilityBinds[AbilityInputIndex];
	if(!Ability->bIsPredicted && GetOwnerRole() < ROLE_Authority)
	{
		return;
	}

	if(Ability)
	{
		Ability->InputPressed();
	}
}

void UTAbilitySystemComponent::ServerAbilityInputPressed_Implementation(ETCharacterInputAction AbilitInputIndex)
{
	// AbilityInputPressed(AbilitInputIndex);
}

bool UTAbilitySystemComponent::ServerAbilityInputPressed_Validate(ETCharacterInputAction AbilitInputIndex)
{
	return true;
}

void UTAbilitySystemComponent::AbilityInputReleased(ETCharacterInputAction AbilityInput)
{
	
}

void UTAbilitySystemComponent::BindAbility(
	TTuple<TEnumAsByte<ETCharacterInputAction>, TSubclassOf<UTAbility>> AbilityBind)
{
	UTAbility* NewAbility = NewObject<UTAbility>(GetOuter(),
	                                             AbilityBind.Value);
	NewAbility->BindAbilityToCharacter(GetOwner());
	OwnedAbilities.Add(NewAbility);

	AbilityBinds.Add(AbilityBind.Key, NewAbility);
}

void UTAbilitySystemComponent::BindDefaultAbilities()
{
	for (auto AbilityBind : DefaultAbilities)
	{
		BindAbility(AbilityBind);
	}
}
