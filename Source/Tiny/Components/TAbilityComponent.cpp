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
}

void UTAbilityComponent::ActivateAbility(const int32 AbilityIndex)
{
	UE_LOG(LogTemp,
	       Display,
	       TEXT("Attempting to activate ability index:%i"),
	       AbilityIndex);
}

void UTAbilityComponent::SetupInput(UInputComponent* InputComponent)
{
	PlayerInputComponent = InputComponent;
}

void UTAbilityComponent::BindAbility(
	TTuple<TEnumAsByte<ETCharacterInputAction>, TSubclassOf<UTAbility>> AbilityBind)
{
	ensure(PlayerInputComponent);

	UTAbility* NewAbility = NewObject<UTAbility>(GetOuter(),
	                                             AbilityBind.Value);

	NewAbility->BindAbilityToCharacter(GetOwner());
	OwnedAbilities.Add(NewAbility);
	
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ETCharacterInputAction"), true);
	auto BindName = EnumPtr->GetNameStringByIndex((int32)AbilityBind.Key);
	
	
	PlayerInputComponent->BindAction(*BindName,
	                                 IE_Pressed,
	                                 NewAbility,
	                                 &UTAbility::InputPressed);
	PlayerInputComponent->BindAction(*BindName,
    	                                 IE_Released,
    	                                 NewAbility,
    	                                 &UTAbility::InputReleased);

	OnAbilityBound.Broadcast(NewAbility);
}
