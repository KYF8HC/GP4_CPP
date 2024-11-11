#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GP4_PlayerState.generated.h"


UCLASS(Abstract)
class GP04_CATCHEM_SHEEP_API AGP4_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void ResetPlayerState();


};
