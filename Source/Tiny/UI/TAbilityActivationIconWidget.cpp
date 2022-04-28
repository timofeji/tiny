// Fill out your copyright notice in the Description page of Project Settings.


#include "TAbilityActivationIconWidget.h"

#include "Components/Image.h"
#include "Components/TimelineComponent.h"

void UTAbilityActivationIconWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTAbilityActivationIconWidget::InitFromAbility(UTAbility* Ability)
{
	if (Ability->AbilityIcon)
	{
		// Ability->AbilityIcon
		IconMatInstance = UMaterialInstanceDynamic::Create(IconMaterial,
		                                                   this);
		IconMatInstance->SetScalarParameterValue("Progress",
		                                         1.f);
		IconMatInstance->SetTextureParameterValue("Icon",
		                                          Ability->AbilityIcon);
		AbilityIcon->SetBrushFromMaterial(IconMatInstance);
	}


	Ability->OnAbilityActivated.AddLambda([this](FActivationData& Data)
	{
		IconMatInstance->SetScalarParameterValue("Progress", 0.f);
		PlayAnimation(ActivateAnimation);
		CoolDownTime= 3.f;
	});

	Ability->OnAbilityEnded.AddLambda([this]
	{
		PlayAnimation(EndActivationAnimation);
		IconMatInstance->SetScalarParameterValue("Progress", 1.f);
	});
}

void UTAbilityActivationIconWidget::NativeTick(const FGeometry& MyGeometry,
	float InDeltaTime)
{
	Super::NativeTick(MyGeometry,
	                  InDeltaTime);

	if(CoolDownTime > 0)
	{
		CoolDownTime -= InDeltaTime;

		IconMatInstance->SetScalarParameterValue("Progress", CoolDownTime);
	}
}
