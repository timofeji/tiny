// Fill out your copyright notice in the Description page of Project Settings.


#include "TAbilityActivationIconWidget.h"

#include "Components/Image.h"

void UTAbilityActivationIconWidget::InitFromAbility(UTAbility* Ability)
{
	if (Ability->AbilityIcon)
	{
		// Ability->AbilityIcon
		IconMatInstance = UMaterialInstanceDynamic::Create(IconMaterial,
		                                                   this);
		
		IconMatInstance->SetScalarParameterValue("Progress", 1.f);
		IconMatInstance->SetTextureParameterValue("Icon", Ability->AbilityIcon);
		AbilityIcon->SetBrushFromMaterial(IconMatInstance);
	}


	Ability->OnAbilityActivated.AddLambda([]
	{
		// IconMatInstance->SetScalarParameterValue("Progress", 0);
	});
}
