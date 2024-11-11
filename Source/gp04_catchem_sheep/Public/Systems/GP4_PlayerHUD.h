#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GP4_PlayerHUD.generated.h"

class UGP4_MenuBase;
class AGP4_GameMode;

UCLASS(Abstract)
class GP04_CATCHEM_SHEEP_API AGP4_PlayerHUD : public AHUD
{
	GENERATED_BODY()

public:

	/* Pooling all the menus, and caching references for them */
	void InitializeMenus();

#pragma region Menu Transitions
	/* Normally would do all of this with a state machine same as in game mode but since some of the menus are in different
	 * levels there is no need to have a state machine for the HUD. Reason for it would be for example having a universally
	 * working Back button functionality every time you change menus you save which state you came from 
	 * and when you press back you go back to that state
	 */
	UFUNCTION(BlueprintCallable)
	void StartGame();

	UFUNCTION(BlueprintCallable)
	void PreRunGame();

	UFUNCTION(BlueprintCallable)
	void RunGameState();

	UFUNCTION(BlueprintCallable)
	void OpenPauseMenu();

	UFUNCTION(BlueprintCallable)
	void OpenOptionsMenu();

	UFUNCTION(BlueprintCallable)
	void OpenAudioMenu();

	UFUNCTION(BlueprintCallable)
	void OpenResolutionMenu();

	UFUNCTION(BlueprintCallable)
	void OpenControlsMenu();

	UFUNCTION(BlueprintCallable)
	void ResumeGame();

	UFUNCTION(BlueprintCallable)
	void WinGame();

	UFUNCTION(BlueprintCallable)
	void LoseGame();

	UFUNCTION(BlueprintCallable)
	void RemoveCurrentMenu();
#pragma endregion
	
	void SetGameModeRef(AGP4_GameMode* GameMode) noexcept { GameModeRef = GameMode; }
	
private:
	
#pragma region Menu References
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menus", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> TutorialMenuClass{};
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGP4_MenuBase> TutorialMenuRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menus", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> InGameHudClass{};
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGP4_MenuBase> InGameHudRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menus", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> LetterGUIClass{};
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGP4_MenuBase> LetterGUIRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menus", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> StartScreenClass{};
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGP4_MenuBase> StartScreenRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menus", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PauseMenuClass{};
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGP4_MenuBase> PauseMenuRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menus", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PauseOptionsMenuClass{};
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGP4_MenuBase> PauseOptionsMenuRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menus", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> AudioMenuClass{};
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGP4_MenuBase> AudioMenuRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menus", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> ResolutionMenuClass{};
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGP4_MenuBase> ResolutionMenuRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menus", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> ControlsMenuClass{};
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGP4_MenuBase> ControlsMenuRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menus", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> WinMenuClass{};
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGP4_MenuBase> WinMenuRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menus", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> LoseMenuClass{};
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGP4_MenuBase> LoseMenuRef{};
	
	UPROPERTY()
	TObjectPtr<UGP4_MenuBase> CurrentMenuWidget{};
#pragma endregion
	
	UPROPERTY(BlueprintReadOnly, Category = "References", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AGP4_GameMode> GameModeRef{};
	
	void ChangeMenu(UGP4_MenuBase* NewMenu);
};
