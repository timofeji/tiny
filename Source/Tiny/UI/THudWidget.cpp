// Fill out your copyright notice in the Description page of Project Settings.


#include "THudWidget.h"
#include "TAbilityActivationIconWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Tiny/Gameplay/TAbility.h"

void UTHudWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTHudWidget::BindAbility(UTAbility* Ability)
{
	auto NewAbilityIcon = CreateWidget<UTAbilityActivationIconWidget>(this,
		AbilityIconClass);

	if(!NewAbilityIcon)
	{
		return;
	}
	
	if (Ability->AbilityIcon)
	{
		NewAbilityIcon->AbilityIcon->SetBrushFromTexture(Ability->AbilityIcon);
	}

	if (AbilityIconContainer)
	{
		AbilityIconContainer->AddChildToHorizontalBox(NewAbilityIcon);
	}
}
