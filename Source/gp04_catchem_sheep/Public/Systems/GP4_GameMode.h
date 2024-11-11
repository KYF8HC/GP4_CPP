#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GP4_GameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStateChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShearedSheepCountChanged, int, SheardSheepCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int, Score);

#pragma region Forward Declarations
class AGP4_PickupSpawner;
class AGP4_PlayerState;
class AGP4_PlayerHUD;
class AGP4_PlayerController;
class AGP4_PlayerCharacter;
#pragma endregion

#pragma region Enums
UENUM(BlueprintType)
enum class EGameState : uint8
{
	None,
	PreCameraSequence,
	StartGame,
	PreRunGame,
	GameRunning,
	PauseGame,
	ResumeGame,
	GameWon,
	GameOver
};
#pragma endregion

UCLASS(Abstract)
class GP04_CATCHEM_SHEEP_API AGP4_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGP4_GameMode();
#pragma region Variables
	UPROPERTY(BlueprintReaDWrite)
	FVector UnstuckPoint;
#pragma endregion

#pragma region Events
	UPROPERTY(BlueprintAssignable)
	FOnGameStateChanged OnLoseGame;
	UPROPERTY(BlueprintAssignable)
	FOnGameStateChanged OnWinGame;
	UPROPERTY(BlueprintAssignable)
	FOnShearedSheepCountChanged OnShearedSheepCountChanged;
	UPROPERTY(BlueprintAssignable)
	FOnScoreChanged OnScoreChanged;
#pragma endregion
	
#pragma region GameState
    /* Changes the game state */
	UFUNCTION(BlueprintCallable)
	void ChangeGameState(EGameState NewState, EGameState PreviousState, bool bShouldLog = false);
	
	UFUNCTION(BlueprintNativeEvent)
	void StartGame();
	
	UFUNCTION(BlueprintNativeEvent)
	void PreRunGame();
	
	UFUNCTION(BlueprintNativeEvent)
	void RunGame();

	UFUNCTION(BlueprintNativeEvent)
	void PauseGame();

	UFUNCTION(BlueprintNativeEvent)
	void ResumeGame();

	UFUNCTION(BlueprintNativeEvent)
	void RestartGame();

	UFUNCTION(BlueprintNativeEvent)
	void QuitGame();
#pragma endregion
	
	UFUNCTION(BlueprintCallable)
	void IncreaseSheepCount() noexcept { NumberOfSheep++; }
	UFUNCTION(BlueprintCallable)
	void IncreaseSheepShearedCount();
	
#pragma region Setters and Getters
	UFUNCTION(BlueprintCallable)
	int GetSheepCount() const noexcept { return NumberOfSheep; }
	UFUNCTION(BlueprintCallable)
	int GetSheepShearedCount() const noexcept { return NumberOfSheepSheared; }
	UFUNCTION(BlueprintCallable)
	float GetTimeRemaining() const noexcept { return GetWorld()->GetTimerManager().GetTimerRemaining(GameTimerHandle); }
	UFUNCTION(BlueprintCallable)
	int GetPlayerScore() const noexcept { return PlayerScore; }
	UFUNCTION(BlueprintCallable)
	void AddPlayerScore(int Score) noexcept;
	UFUNCTION(BlueprintCallable)
	EGameState GetCurrentGameState() const noexcept { return CurrentGameState; }
#pragma endregion
	
protected:

	virtual void StartPlay() override;

private:

#pragma region Variables and References
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game", meta = (AllowPrivateAccess = "true"))
	uint8 NumberOfSheep{};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game", meta = (AllowPrivateAccess = "true"))
	uint8 NumberOfSheepSheared{};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timers", meta = (AllowPrivateAccess = "true"))
	int GameDuration{100};
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timers", meta = (AllowPrivateAccess = "true"))
	int CountdownDuration{3};
	UPROPERTY(BlueprintReadWrite, Category = "Game", meta = (AllowPrivateAccess = "true"))
	int PlayerScore{};
	UPROPERTY(BlueprintReadWrite, Category = "Game", meta = (AllowPrivateAccess = "true"))
	bool bHasAllLetters{false};
	
	//Timers
	UPROPERTY()
	bool bShouldUseCountdown{false};
	UPROPERTY()
	FTimerHandle CountdownTimerHandle{};
	UPROPERTY()
	FTimerHandle GameTimerHandle{};

	//Main References
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<AGP4_PlayerCharacter> PlayerCharacterRef{};
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<AGP4_PlayerState> PlayerStateRef{};
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<AGP4_PlayerController> PlayerControllerRef{};
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<AGP4_PlayerHUD> PlayerHUDRef{};

	//Pickup Ref
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGP4_PickupSpawner> PickupSpawnerClass{};
	UPROPERTY()
	TObjectPtr<AGP4_PickupSpawner> PickupSpawnerRef{};

	EGameState CurrentGameState{EGameState::None};
#pragma endregion

	/* ----------------- Functions ----------------- */
	void SaveReferences();
	void CreateSystems();
	void OnCountDownFinished();
	void OnGameTimerFinished();
};
