#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GP4_MenuBase.generated.h"

class AGP4_PlayerHUD;
class AGP4_GameMode;
class UCanvasPanel;

UCLASS()
class GP04_CATCHEM_SHEEP_API UGP4_MenuBase : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void EnableMenu(bool bShouldEnable);

	UFUNCTION(BlueprintImplementableEvent)
	void InitializeMenu();
	
	void SetGameModeRef(AGP4_GameMode* GameMode) noexcept { GameModeRef = GameMode; }
	void SetHUDRef(AGP4_PlayerHUD* HUD) noexcept { HUDRef = HUD; }
private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menu", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UCanvasPanel> MenuCanvasRef{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "References", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AGP4_GameMode> GameModeRef{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "References", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AGP4_PlayerHUD> HUDRef{};
	
};
