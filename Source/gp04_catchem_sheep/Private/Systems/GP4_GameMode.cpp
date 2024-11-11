#include "Systems/GP4_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Pickups/GP4_PickupSpawner.h"
#include "Systems/GP4_PlayerCharacter.h"
#include "Systems/GP4_PlayerController.h"
#include "Systems/GP4_PlayerHUD.h"
#include "Systems/GP4_PlayerState.h"
#include "Utils/GP4_UtilsFunctionLibrary.h"

AGP4_GameMode::AGP4_GameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

#pragma region GameState

void AGP4_GameMode::StartGame_Implementation()
{
	PlayerHUDRef->StartGame();
	EnableInput(PlayerControllerRef);
}

void AGP4_GameMode::PreRunGame_Implementation()
{
	if (bShouldUseCountdown)
		GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &AGP4_GameMode::OnCountDownFinished,
		                                       CountdownDuration, false);
	PlayerHUDRef->PreRunGame();
	PlayerCharacterRef->SetReceiveInput(false);
}

void AGP4_GameMode::RunGame_Implementation()
{
	PlayerControllerRef->SetInputMode(FInputModeGameOnly());
	PlayerCharacterRef->SetReceiveInput(true);
	PickupSpawnerRef->SpawnInitialPickups();
	PlayerHUDRef->RunGameState();

	GetWorld()->GetTimerManager().SetTimer(GameTimerHandle, this, &AGP4_GameMode::OnGameTimerFinished, GameDuration,
	                                       false);
}

void AGP4_GameMode::PauseGame_Implementation()
{
	PlayerControllerRef->SetInputModeToUIOnly();
}

void AGP4_GameMode::ResumeGame_Implementation()
{
	PlayerControllerRef->SetInputModeToGameOnly();
}

void AGP4_GameMode::RestartGame_Implementation()
{
	PlayerStateRef->ResetPlayerState();
}

void AGP4_GameMode::QuitGame_Implementation()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerControllerRef, EQuitPreference::Quit, false);
}

void AGP4_GameMode::ChangeGameState(EGameState NewState, EGameState PreviousState, bool bShouldLog)
{
	if (CurrentGameState == NewState)
	{
		return;
	}

	CurrentGameState = NewState;
	if (bShouldLog)
	{
		UE_LOG(LogTemp, Log, TEXT("AGP4_GameMode::ChangeGameState: %s"),
		       *UGP4_UtilsFunctionLibrary::GetGameStateAsString(NewState));
	}

	switch (NewState)
	{
	case EGameState::None: break;

	case EGameState::StartGame:
		StartGame();
		break;

	case EGameState::PreRunGame:
		PreRunGame();
		break;

	case EGameState::GameRunning:
		RunGame();
		break;

	case EGameState::PauseGame:
		PauseGame();
		break;

	case EGameState::ResumeGame:
		ResumeGame();
		break;

	case EGameState::GameWon:
		OnWinGame.Broadcast();
		PlayerHUDRef->WinGame();
		GetWorld()->GetTimerManager().ClearTimer(GameTimerHandle);
		PlayerControllerRef->EndGame();
		break;

	case EGameState::GameOver:
		OnLoseGame.Broadcast();
		PlayerHUDRef->LoseGame();
		GetWorld()->GetTimerManager().ClearTimer(GameTimerHandle);
		PlayerControllerRef->EndGame();
		break;

	default: break;
	}
}
#pragma endregion

#pragma region Helpers
void AGP4_GameMode::IncreaseSheepShearedCount()
{
	NumberOfSheepSheared++;
	OnShearedSheepCountChanged.Broadcast(NumberOfSheepSheared);
	if (NumberOfSheepSheared == NumberOfSheep)
	{
		ChangeGameState(EGameState::GameWon, EGameState::GameRunning);
	}
}

void AGP4_GameMode::AddPlayerScore(int Score) noexcept
{
	Score *= 10;
	PlayerScore += Score;
	OnScoreChanged.Broadcast(Score);
}
#pragma endregion

#pragma region Engine Callbacks

void AGP4_GameMode::StartPlay()
{
	Super::StartPlay();

	CreateSystems();
	SaveReferences();

	ChangeGameState(EGameState::StartGame, EGameState::None);
}
#pragma endregion

#pragma region Internal
void AGP4_GameMode::SaveReferences()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn)
	{
		PlayerCharacterRef = Cast<AGP4_PlayerCharacter>(PlayerPawn);
		checkf(PlayerCharacterRef, TEXT("AGP4_GameMode::SaveReferences: Player is not valid"));
		PlayerCharacterRef->SetPickupSpawner(PickupSpawnerRef);
	}

	APlayerState* PlayerState = UGameplayStatics::GetPlayerState(GetWorld(), 0);
	if (PlayerState)
	{
		PlayerStateRef = Cast<AGP4_PlayerState>(PlayerState);
		checkf(PlayerStateRef, TEXT("AGP4_GameMode::SaveReferences: PlayerState is not valid"));
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerControllerRef = Cast<AGP4_PlayerController>(PlayerController);
		checkf(PlayerControllerRef, TEXT("AGP4_GameMode::SaveReferences: PlayerController is not valid"));
		PlayerControllerRef->SetGameModeRef(this);
	}

	if (PlayerControllerRef)
	{
		PlayerHUDRef = Cast<AGP4_PlayerHUD>(PlayerControllerRef->GetHUD());
		checkf(PlayerHUDRef, TEXT("AGP4_GameMode::SaveReferences: HUD is not valid"));
		PlayerHUDRef->SetGameModeRef(this);
		PlayerHUDRef->InitializeMenus();
	}
	PlayerCharacterRef->InitializePlayer();
}

void AGP4_GameMode::CreateSystems()
{
	//PickupSpawner
	checkf(PickupSpawnerClass, TEXT("AGP4_GameMode::CreateSystems: PickupSpawnerClass is nullptr"));
	PickupSpawnerRef = GetWorld()->SpawnActor<AGP4_PickupSpawner>(PickupSpawnerClass);
	if (!PickupSpawnerRef)
	{
		UE_LOG(LogTemp, Error, TEXT("AGP4_GameMode::CreateSystems: PickupSpawnerRef is nullptr"));
	}
}

void AGP4_GameMode::OnCountDownFinished()
{
	ChangeGameState(EGameState::GameRunning, EGameState::StartGame);
}

void AGP4_GameMode::OnGameTimerFinished()
{
	ChangeGameState(EGameState::GameOver, EGameState::GameRunning);
}

#pragma endregion
