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

	NewAbilityIcon->InitFromAbility(Ability);

	if(!NewAbilityIcon)
	{
		return;
	}
	

	if (AbilityIconContainer)
	{
		AbilityIconContainer->AddChildToHorizontalBox(NewAbilityIcon);
	}
}
