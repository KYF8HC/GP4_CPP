#include "Systems/GP4_PlayerCharacter.h"
#include "Actions/GP4_ProjectileAction.h"
#include "Camera/CameraComponent.h"
#include "Components/GP4_ActionComponent.h"
#include "Components/SphereComponent.h"
#include "InteractableSystem/GP4_ObjectInteractorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


AGP4_PlayerCharacter::AGP4_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponentRef = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponentRef->SetupAttachment(RootComponent);

	CameraComponentRef = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponentRef->SetupAttachment(SpringArmComponentRef);

	ActionComponentRef = CreateDefaultSubobject<UGP4_ActionComponent>(TEXT("ActionComponent"));

	ObjectInteractor = CreateDefaultSubobject<UGP4ObjectInteractorComponent>(TEXT("ObjectInteractor"));
	ObjectInteractor->SetupAttachment(RootComponent);

	ObjectInteractor->TriggerArea->SetupAttachment(ObjectInteractor);
	for (int i = 0; i < ObjectInteractor->HoldLocationMap.Num(); i++)
	{
		ObjectInteractor->HoldLocationMap[(EInteractableType)(i + 1)]->SetupAttachment(ObjectInteractor);
	}


	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

#pragma region Input handling
void AGP4_PlayerCharacter::HandleMove(FVector2D Input)
{
	if (!bShouldReceiveInput)
		return;
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;

	const FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);

	AddMovementInput(ControlRotation.Vector(), Input.Y);
	AddMovementInput(RightVector, Input.X);
}

void AGP4_PlayerCharacter::HandleLook(FVector2D Input)
{
	if (!bShouldReceiveInput)
		return;
	AddControllerYawInput(Input.X);
	AddControllerPitchInput(Input.Y);
}

void AGP4_PlayerCharacter::HandleUseItem()
{
	if (!bShouldReceiveInput)
		return;
	ActionComponentRef->StartEquippedAction(this);
}

void AGP4_PlayerCharacter::HandleStopItem()
{
	if (!bShouldReceiveInput)
		return;
	ActionComponentRef->StopEquippedAction(this);
}

void AGP4_PlayerCharacter::HandleExecuteAction()
{
	if (!bShouldReceiveInput)
		return;

	UGP4_ProjectileAction* ProjectileAction = Cast<UGP4_ProjectileAction>(
		ActionComponentRef->GetCurrentEquippedAction());

	if (!ProjectileAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("AGP4_PlayerCharacter::HandleExecuteAction: No equipped projectile action."));
		return;
	}

	if (ProjectileAction->IsRunning())
	{
		OnThrow.Broadcast();
		ProjectileAction->ExecuteAction(this);
	}
}

void AGP4_PlayerCharacter::StopMovement()
{
	GetCharacterMovement()->StopMovementImmediately();
	bShouldReceiveInput = false;
}

void AGP4_PlayerCharacter::SetUseControllerRotation(bool bShouldUse)
{
	bUseControllerRotationYaw = bShouldUse;
}
#pragma endregion

void AGP4_PlayerCharacter::InitializePlayer_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("AGP4_PlayerCharacter::InitializePlayer_Implementation: Player Initialized"));
}

void AGP4_PlayerCharacter::SetPickupSpawner(AGP4_PickupSpawner* Spawner) const
{
	ActionComponentRef->SetPickupSpawner(Spawner);
}

void AGP4_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(PlayerTag);
}
