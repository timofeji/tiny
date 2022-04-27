// Fill out your copyright notice in the Description page of Project Settings.


#include "TAbility_AOEHeal.h"


UTAbility_AOEHeal::UTAbility_AOEHeal()
{
	
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UTexture2D> Icon;

		FConstructorStatics()
			: Icon(
				TEXT("Texture2D'/Game/UI/IconTextures/T_UI_AOEHeal.T_UI_AOEHeal'"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	AbilityIcon = ConstructorStatics.Icon.Object;
}
