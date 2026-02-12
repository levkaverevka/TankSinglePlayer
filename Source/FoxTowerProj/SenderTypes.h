#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

UENUM(BlueprintType)
enum class ESenderTypes : uint8
{
	FromHealthWidget UMETA(DisplayName = "From Widget"),
	FromTank UMETA(DisplayName = "From Tank")
};

