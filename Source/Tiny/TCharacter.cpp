// Fill out your copyright notice in the Description page of Project Settings.


#include "TCharacter.h"

#include "Blueprint/UserWidget.h"
#include "Components/TAbilitySystemComponent.h"
#include "Gameplay/TAbility.h"
#include "Kismet/GameplayStatics.h"
#include "UI/THudWidget.h"


// Sets default values
ATCharacter::ATCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	AbilityComponent = CreateDefaultSubobject<UTAbilitySystemComponent>(
		TEXT("Ability Component"));
}

UTHudWidget* ATCharacter::GetHUD()
{
	return HUDWidget;
}

void ATCharacter::ClientInit()
{
	AbilityComponent->BindDefaultAbilities();
	
	CreateDefaultUI();

	if (ensureAlwaysMsgf(AbilityComponent,
						 TEXT("TAbilitySystem not initialized properly")))
	{
		AbilityComponent->OnAbilityBound.AddLambda([this](UTAbility* Ability)
		{
			if(HUDWidget)
			{
				HUDWidget->BindAbility(Ability);
			}
		});

		AbilityComponent->OnAbilityRemoved.AddLambda([this](UTAbility* Ability)
		{
			if(HUDWidget)
			{
				HUDWidget->RemoveAbility(Ability);
			}
		});
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("CLIENT INIT"));

	AbilityComponent->SetupDefaultInput(InputComponent);
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
}

void ATCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	AddMovementInput(ControlRot.Vector(), Value);
}

void ATCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, Value);
}

// Called to bind functionality to input
void ATCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",
	                               this,
	                               &ATCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",
	                               this,
	                               &ATCharacter::MoveRight);
}
