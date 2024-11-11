#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GP4_Button.generated.h"


class UTextBlock;
class UButton;

UCLASS()
class GP04_CATCHEM_SHEEP_API UGP4_Button : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Button", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UButton> ButtonRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Button", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UTextBlock> ButtonText{};
};