#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GP4_PlayerController.generated.h"

class AGP4_GameMode;
class AGP4_PlayerCharacter;
class UEnhancedInputComponent;
class UEnhancedInputLocalPlayerSubsystem;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS(Abstract)
class GP04_CATCHEM_SHEEP_API AGP4_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void SetInputModeToUIOnly();

	UFUNCTION(BlueprintCallable)
	void SetInputModeToGameOnly();
	
	void EndGame();
	void SetGameModeRef(AGP4_GameMode* GameMode) { GameModeRef = GameMode; }
	
protected:

	virtual void OnPossess(APawn* aPawn) override;

private:

#pragma region Input Actions
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> MappingContext{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Move{};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Look{};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> UseItem{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ExecuteAction{};
#pragma endregion

#pragma region System References	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AGP4_PlayerCharacter> PlayerCharacterRef{};

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponentRef{};

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystemRef{};

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AGP4_GameMode> GameModeRef{};
#pragma endregion

	void BindInputActions();
	void HandleMove(const FInputActionValue& Value);
	void HandleLook(const FInputActionValue& Value);
	void HandleUseItem();
	void HandleStopItem();
	void HandleExecuteAction();
};
