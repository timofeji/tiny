#pragma once

#include "TTypes.generated.h"

UENUM(BlueprintType, meta=(Bitflags,UseEnumValuesAsMaskValuesInEditor="true"))
enum class ETCharacterInputAction : uint8
{
	NONE = 0 UMETA(Hidden),
	Attack = 1 << 0,
	Spell1 = 1 << 1,
	Spell2 = 1 << 2,
	Spell3 = 1 << 3,
};
ENUM_CLASS_FLAGS(ETCharacterInputAction);