#include "Systems/GP4_PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "GUI/GP4_MenuBase.h"


void AGP4_PlayerHUD::InitializeMenus()
{
	if (!ensureMsgf(TutorialMenuClass, TEXT("AGP4_PlayerHUD::InitializeMenus: TutorialMenuClass is nullptr!")))
		return;
	TutorialMenuRef = CreateWidget<UGP4_MenuBase>(GetWorld(), TutorialMenuClass);
	TutorialMenuRef->SetGameModeRef(GameModeRef);
	TutorialMenuRef->SetHUDRef(this);
	TutorialMenuRef->InitializeMenu();

	if (!ensureMsgf(InGameHudClass, TEXT("AGP4_PlayerHUD::InitializeMenus: InGameHudClass is nullptr!")))
		return;
	InGameHudRef = CreateWidget<UGP4_MenuBase>(GetWorld(), InGameHudClass);
	InGameHudRef->SetGameModeRef(GameModeRef);
	InGameHudRef->SetHUDRef(this);
	InGameHudRef->InitializeMenu();

	if (!ensureMsgf(LetterGUIClass, TEXT("AGP4_PlayerHUD::InitializeMenus: LetterGUIClass is nullptr!")))
		return;
	LetterGUIRef = CreateWidget<UGP4_MenuBase>(GetWorld(), LetterGUIClass);
	LetterGUIRef->SetGameModeRef(GameModeRef);
	LetterGUIRef->SetHUDRef(this);
	LetterGUIRef->InitializeMenu();

	if (!ensureMsgf(StartScreenClass, TEXT("AGP4_PlayerHUD::InitializeMenus: StartScreenClass is nullptr!")))
		return;
	StartScreenRef = CreateWidget<UGP4_MenuBase>(GetWorld(), StartScreenClass);
	StartScreenRef->SetGameModeRef(GameModeRef);
	StartScreenRef->SetHUDRef(this);
	StartScreenRef->InitializeMenu();

	if (!ensureMsgf(PauseMenuClass, TEXT("AGP4_PlayerHUD::InitializeMenus: PauseMenuClass is nullptr!")))
		return;
	PauseMenuRef = CreateWidget<UGP4_MenuBase>(GetWorld(), PauseMenuClass);
	PauseMenuRef->SetGameModeRef(GameModeRef);
	PauseMenuRef->SetHUDRef(this);
	PauseMenuRef->InitializeMenu();

	if (!ensureMsgf(PauseOptionsMenuClass, TEXT("AGP4_PlayerHUD::InitializeMenus: PauseOptionsMenuClass is nullptr!")))
		return;
	PauseOptionsMenuRef = CreateWidget<UGP4_MenuBase>(GetWorld(), PauseOptionsMenuClass);
	PauseOptionsMenuRef->SetGameModeRef(GameModeRef);
	PauseOptionsMenuRef->SetHUDRef(this);
	PauseOptionsMenuRef->InitializeMenu();

	if (!ensureMsgf(AudioMenuClass, TEXT("AGP4_PlayerHUD::InitializeMenus: AudioMenuClass is nullptr!")))
		return;
	AudioMenuRef = CreateWidget<UGP4_MenuBase>(GetWorld(), AudioMenuClass);
	AudioMenuRef->SetGameModeRef(GameModeRef);
	AudioMenuRef->SetHUDRef(this);
	AudioMenuRef->InitializeMenu();

	if (!ensureMsgf(ResolutionMenuClass, TEXT("AGP4_PlayerHUD::InitializeMenus: ResolutionMenuClass is nullptr!")))
		return;
	ResolutionMenuRef = CreateWidget<UGP4_MenuBase>(GetWorld(), ResolutionMenuClass);
	ResolutionMenuRef->SetGameModeRef(GameModeRef);
	ResolutionMenuRef->SetHUDRef(this);
	ResolutionMenuRef->InitializeMenu();

	if (!ensureMsgf(ControlsMenuClass, TEXT("AGP4_PlayerHUD::InitializeMenus: ControlsMenuClass is nullptr!")))
		return;
	ControlsMenuRef = CreateWidget<UGP4_MenuBase>(GetWorld(), ControlsMenuClass);
	ControlsMenuRef->SetGameModeRef(GameModeRef);
	ControlsMenuRef->SetHUDRef(this);
	ControlsMenuRef->InitializeMenu();

	if (!ensureMsgf(WinMenuClass, TEXT("AGP4_PlayerHUD::InitializeMenus: WinMenuClass is nullptr!")))
		return;
	WinMenuRef = CreateWidget<UGP4_MenuBase>(GetWorld(), WinMenuClass);
	WinMenuRef->SetGameModeRef(GameModeRef);
	WinMenuRef->SetHUDRef(this);
	WinMenuRef->InitializeMenu();

	if (!ensureMsgf(LoseMenuClass, TEXT("AGP4_PlayerHUD::InitializeMenus: LoseMenuClass is nullptr!")))
		return;
	LoseMenuRef = CreateWidget<UGP4_MenuBase>(GetWorld(), LoseMenuClass);
	LoseMenuRef->SetGameModeRef(GameModeRef);
	LoseMenuRef->SetHUDRef(this);
	LoseMenuRef->InitializeMenu();
}

#pragma region Menu Transitions
void AGP4_PlayerHUD::StartGame()
{
	ChangeMenu(StartScreenRef);
}

void AGP4_PlayerHUD::PreRunGame()
{
	ChangeMenu(TutorialMenuRef);
}

void AGP4_PlayerHUD::RunGameState()
{
	ChangeMenu(InGameHudRef);

	//TODO: Figure out a way to make this automatic?? Right now it only happens on Pause/Resume so maybe fine?
	if (!LetterGUIRef->IsInViewport())
		LetterGUIRef->EnableMenu(true);
}

void AGP4_PlayerHUD::OpenPauseMenu()
{
	ChangeMenu(PauseMenuRef);
	//The letter pickup stuff is also on the Viewport
	//So we need to make sure it's not visible
	if (LetterGUIRef->IsInViewport())
		LetterGUIRef->EnableMenu(false);
}

void AGP4_PlayerHUD::OpenOptionsMenu()
{
	ChangeMenu(PauseOptionsMenuRef);
}

void AGP4_PlayerHUD::OpenAudioMenu()
{
	ChangeMenu(AudioMenuRef);
}

void AGP4_PlayerHUD::OpenResolutionMenu()
{
	ChangeMenu(ResolutionMenuRef);
}

void AGP4_PlayerHUD::OpenControlsMenu()
{
	ChangeMenu(ControlsMenuRef);
}

void AGP4_PlayerHUD::ResumeGame()
{
	//It's the same as RunGameState
	//Might not be necessary to have this
	//But maybe we want to do something else when resuming the game
	ChangeMenu(InGameHudRef);
	if (!LetterGUIRef->IsInViewport())
		LetterGUIRef->EnableMenu(true);
}

void AGP4_PlayerHUD::WinGame()
{
	ChangeMenu(WinMenuRef);
}

void AGP4_PlayerHUD::LoseGame()
{
	ChangeMenu(LoseMenuRef);
}

void AGP4_PlayerHUD::RemoveCurrentMenu()
{
	if (CurrentMenuWidget)
		CurrentMenuWidget->EnableMenu(false);
	CurrentMenuWidget = nullptr;
}

void AGP4_PlayerHUD::ChangeMenu(UGP4_MenuBase* NewMenu)
{
	if (CurrentMenuWidget)
		CurrentMenuWidget->EnableMenu(false);
	NewMenu->EnableMenu(true);
	CurrentMenuWidget = NewMenu;
}
#pragma endregion
