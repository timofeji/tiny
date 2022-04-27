// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "THudWidget.generated.h"

class UTAbility;

class UTAbilityActivationIconWidget;
class UHorizontalBox;
/**
 * 
 */
UCLASS()
class TINY_API UTHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	

	TArray<UTAbilityActivationIconWidget*> AbilityIcons;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UHorizontalBox* AbilityIconContainer;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> AbilityIconClass;


	UFUNCTION(BlueprintCallable)
	void BindAbility(UTAbility* Ability);
};
