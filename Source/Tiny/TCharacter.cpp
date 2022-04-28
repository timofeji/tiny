// Fill out your copyright notice in the Description page of Project Settings.


#include "TCharacter.h"

#include "Blueprint/UserWidget.h"
#include "Components/TAbilityComponent.h"
#include "Gameplay/TAbility.h"
#include "Kismet/GameplayStatics.h"
#include "UI/THudWidget.h"

//
// ENUM_RANGE_BY_COUNT(ETCharacterInputAction,
//                     ETCharacterInputAction::MAX)


// Sets default values
ATCharacter::ATCharacter()
{
	PrimaryActorTick.bCanEverTick = true;


	AbilityComponent = CreateDefaultSubobject<UTAbilityComponent>(
		TEXT("Ability Component"));

	if (ensureAlwaysMsgf(AbilityComponent,
	                     TEXT("TAbilitySystem not initialized properly")))
	{
		AbilityComponent->OnAbilityBound.AddLambda([this](UTAbility* Ability)
			{
				GetHUD()->BindAbility(Ability);
			}
		);
	}
}

UTHudWidget* ATCharacter::GetHUD()
{
	return HUDWidget;
}

void ATCharacter::BindDefaultAbilities()
{
	check(AbilityComponent)
	AbilityComponent->SetupInput(InputComponent);

	for (auto AbilityBind : DefaultAbilities)
	{
		AbilityComponent->BindAbility(AbilityBind);
	}
}

void ATCharacter::CreateDefaultUI()
{
	if (!HudClass)
	{
		return;
	}


	auto PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),
		0));

	HUDWidget = CreateWidget<UTHudWidget>(PC,
	                                      HudClass);
	HUDWidget->AddToViewport();
}

// Called when the game starts or when spawned
void ATCharacter::BeginPlay()
{
	Super::BeginPlay();

	CreateDefaultUI();
	BindDefaultAbilities();
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


	if (!AbilityComponent)
	{
		return;
	}
}
