// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Tiny/Gameplay/TAbility.h"
#include "TAbilityActivationIconWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class TINY_API UTAbilityActivationIconWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere)
	UMaterialInterface* IconMaterial;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UWidgetAnimation* ActivateAnimation;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UWidgetAnimation* EndActivationAnimation;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* AbilityIcon;
	

	void InitFromAbility(UTAbility* Ability);

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
protected:
	float AbilityCoolDown;
	float  IconCoolDown;
	UMaterialInstanceDynamic* IconMatInstance;
};
