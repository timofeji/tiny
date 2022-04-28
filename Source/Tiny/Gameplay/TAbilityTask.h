// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TGameplayTypes.h"
#include "UObject/Object.h"
#include "TAbilityTask.generated.h"


class UTAbilityTask;

DECLARE_MULTICAST_DELEGATE_OneParam(FTaskEnded, UTAbilityTask*);



USTRUCT(BlueprintType)
struct TINY_API FTAbilityTaskData
{
	
	GENERATED_BODY()

	
	UPROPERTY(EditAnywhere)
	TMap<FName,FTAbilityAttribute> TaskAttributes;


	template <typename FieldType>
	void AddField(FName FieldName, void* FieldValue)
	{
		FTAbilityAttribute NewAttributeField;
		NewAttributeField.ValuePtr = FieldValue;
		TaskAttributes.FindOrAdd(FieldName, NewAttributeField);
	}

	template <typename FieldType>
	FieldType* GetField(FName FieldName)
	{
		return static_cast<FieldType*>(TaskAttributes[FieldName].ValuePtr);
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

	
	virtual void OnExecuteTask(UObject* OwningObject);
	void InitTaskFromData(const FTAbilityTaskData& Data);
	
	FTaskEnded OnEndTask;
	
	FTAbilityTaskData TaskData;
};
