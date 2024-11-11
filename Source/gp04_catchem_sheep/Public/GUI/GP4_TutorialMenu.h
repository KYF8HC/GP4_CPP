#pragma once

#include "CoreMinimal.h"
#include "GP4_MenuBase.h"
#include "GP4_TutorialMenu.generated.h"

class UImage;
class UGP4_Button;

UCLASS()
class GP04_CATCHEM_SHEEP_API UGP4_TutorialMenu : public UGP4_MenuBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buttons", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UGP4_Button> PlayButton{};
};
