// UINTERFACE(BlueprintType)
// class UTEffectRecieverInterface : public UInterface
// {
// 	GENERATED_BODY()
// };
//
// class FLAB_API IInteractableInterface
// {
// 	GENERATED_BODY()
//
// 	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
// 	bool Interact(AFlabCharacter* Interactor);
// 	virtual bool Interact_Implementation(AFlabCharacter* Interactor);
// };


#include "Engine/DataTable.h"
#include "TGameplayTypes.generated.h"


class UTAbility;

USTRUCT()
struct FTCharacterAbilityRow : public FTableRowBase
{

	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTAbility> Ability;

	UPROPERTY(EditAnywhere)
	UTexture2D* AbilityIcon;
};


USTRUCT(BlueprintType)
struct TINY_API FTAbilityAttribute
{
	
	GENERATED_BODY()
	// template <typename FieldType>;
	// typedef;
};
