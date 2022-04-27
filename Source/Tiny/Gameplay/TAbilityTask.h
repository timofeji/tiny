// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TAbilityTask.generated.h"


DECLARE_MULTICAST_DELEGATE(FTaskEnded);

USTRUCT(BlueprintType)
struct TINY_API FTAbilityAttribute
{
	
	GENERATED_BODY()
	// template <typename FieldType>;
	// typedef;
};


USTRUCT(BlueprintType)
struct TINY_API FTAbilityTaskData
{
	
	GENERATED_BODY()

	
	UPROPERTY(EditAnywhere)
	TMap<FName, FTAbilityAttribute> TaskAttributes;


	template <typename FieldType>
	void AddField(FName FieldName, FieldType FieldValue)
	{
		FTAbilityAttribute NewAttributeField;
		
		TaskAttributes.FindOrAdd(FieldName, NewAttributeField);
	}

	bool GetField(FName FieldName)
	{
		return true;
	}
};

/**
 * 
 */
UCLASS()
class TINY_API UTAbilityTask : public UObject
{
	GENERATED_BODY()
public:	
	void EndTask();

	
	virtual void OnExecuteTask();
	void InitTaskFromData(const FTAbilityTaskData& Data);
	
	FTaskEnded OnEndTask;
};
