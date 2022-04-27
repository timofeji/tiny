// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TTypes.h"
#include "GameFramework/Character.h"
#include "TCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FAbilityActivateDelegate,
                          const int32);

class UTHudWidget;
class UTAbilityComponent;
class UTAbility;

USTRUCT(BlueprintType)
struct TINY_API FTAbilityBindInfo
{
	GENERATED_BODY()

	// UPROPERTY(EditAnywhere)
	// TEnumAsByte<ETCharacterInputAction> InputAction;
};

UCLASS()
class TINY_API ATCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATCharacter();

	UTAbilityComponent* AbilityComponent;

	UPROPERTY(EditDefaultsOnly,
		Category=Gameplay)
	TMap<TEnumAsByte<ETCharacterInputAction>, TSubclassOf<UTAbility>> DefaultAbilities;


	UPROPERTY(EditDefaultsOnly,
		Category=UI)
	TSubclassOf<UUserWidget> HudClass;


	UTHudWidget* GetHUD();
protected:
	void BindDefaultAbilities();
	void CreateDefaultUI();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTHudWidget* HUDWidget;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void
	SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
