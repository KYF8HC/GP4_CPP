#include "Actions/GP4_ProjectileAction.h"
#include "Actors/GP4_ProjectileActorBase.h"
#include "Components/GP4_ActionComponent.h"
#include "Systems/GP4_PlayerCharacter.h"

void UGP4_ProjectileAction::Tick_Implementation(float DeltaTime)
{
	Super::Tick_Implementation(DeltaTime);

	if(!ensureAlways(ProjectileClass))
	{
		UE_LOG(LogTemp, Error, TEXT("UGP4_ProjectileAction::Tick_Implementation: ProjectileClass is nullptr"));
		return;
	}
}

void UGP4_ProjectileAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	auto PlayerChar = Cast<AGP4_PlayerCharacter>(OwningActionComponent->GetOwner());
	if(PlayerChar)
	{
		PlayerChar->SetUseControllerRotation(true);
		PlayerChar->OnAim.Broadcast();
	}
}

void UGP4_ProjectileAction::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
	auto PlayerChar = Cast<AGP4_PlayerCharacter>(OwningActionComponent->GetOwner());
	if(PlayerChar)
	{
		PlayerChar->SetUseControllerRotation(false);
		PlayerChar->OnStopAim.Broadcast();
	}
}

void UGP4_ProjectileAction::ExecuteAction_Implementation(AActor* Instigator)
{
	OwningActionComponent->StopEquippedAction(Instigator, true);
	OwningActionComponent->RemoveAction(this, true);
}
