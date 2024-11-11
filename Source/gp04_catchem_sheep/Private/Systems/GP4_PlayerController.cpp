#include "Systems/GP4_PlayerController.h"
#include "Systems/GP4_PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AGP4_PlayerController::SetInputModeToUIOnly()
{
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}

void AGP4_PlayerController::SetInputModeToGameOnly()
{
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void AGP4_PlayerController::EndGame()
{
	SetInputModeToUIOnly();
	PlayerCharacterRef->StopMovement();
}

void AGP4_PlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	PlayerCharacterRef = Cast<AGP4_PlayerCharacter>(aPawn);
	checkf(PlayerCharacterRef, TEXT("AGP4_PlayerController::OnPossess: PlayerController can only possess a Character"));

	if (!InputComponent)
	{
		SetupInputComponent();
		UE_LOG(LogTemp, Error, TEXT("AGP4_PlayerController::OnPossess: InputComponent is nullptr!"));
	}

	EnhancedInputComponentRef = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponentRef, TEXT("AGP4_PlayerController::OnPossess: InputComponentRef is nullptr!"));

	InputSubsystemRef = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	checkf(InputSubsystemRef, TEXT("AGP4_PlayerController::OnPossess: InputSubsystemRef is nullptr!"));
	InputSubsystemRef->AddMappingContext(MappingContext, 0);

	BindInputActions();
}

void AGP4_PlayerController::BindInputActions()
{
	EnhancedInputComponentRef->BindAction(Move, ETriggerEvent::Triggered, this, &AGP4_PlayerController::HandleMove);
	EnhancedInputComponentRef->BindAction(Look, ETriggerEvent::Triggered, this, &AGP4_PlayerController::HandleLook);
	
	EnhancedInputComponentRef->BindAction(UseItem, ETriggerEvent::Triggered, this, &AGP4_PlayerController::HandleUseItem);
	EnhancedInputComponentRef->BindAction(UseItem, ETriggerEvent::Completed, this, &AGP4_PlayerController::HandleStopItem);
	EnhancedInputComponentRef->BindAction(ExecuteAction, ETriggerEvent::Triggered, this, &AGP4_PlayerController::HandleExecuteAction);
}

void AGP4_PlayerController::HandleMove(const FInputActionValue& Value)
{
	PlayerCharacterRef->HandleMove(Value.Get<FVector2D>());
}

void AGP4_PlayerController::HandleLook(const FInputActionValue& Value)
{
	PlayerCharacterRef->HandleLook(Value.Get<FVector2D>());
}

void AGP4_PlayerController::HandleUseItem()
{
	PlayerCharacterRef->HandleUseItem();
}

void AGP4_PlayerController::HandleStopItem()
{
	PlayerCharacterRef->HandleStopItem();
}

void AGP4_PlayerController::HandleExecuteAction()
{
	PlayerCharacterRef->HandleExecuteAction();
}