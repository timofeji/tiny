// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* AbilityIcon;

	

};
