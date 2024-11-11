#include "Components/GP4_ActionComponent.h"
#include "Actions/GP4_Action.h"

UGP4_ActionComponent::UGP4_ActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGP4_ActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<UGP4_Action> ActionClass : DefaultActions)
	{
		AddAction(GetOwner(), ActionClass);
	}
}

UGP4_Action* UGP4_ActionComponent::FindActionByName(FName ActionName) const
{
	for (UGP4_Action* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			return Action;
		}
	}
	return nullptr;
}

void UGP4_ActionComponent::EquipAction(AActor* Instigator, UGP4_Action* NewAction)
{
	if (CurrentEquippedAction != nullptr)
	{
		if (CurrentEquippedAction->IsRunning())
			CurrentEquippedAction->StopAction(Instigator);
		else
		{
			UE_LOG(LogTemp, Log, TEXT("UGP4_ActionComponent::EquipAction: Removing equipped action %s"),
			       *CurrentEquippedAction->ActionName.ToString());
			RemoveAction(CurrentEquippedAction, false);
		}
	}
	CurrentEquippedAction = NewAction;
	OnActionEquipped.Broadcast(this, NewAction, false);
}

void UGP4_ActionComponent::AddAction(AActor* Instigator, TSubclassOf<UGP4_Action> ActionClass, bool bEquip)
{
	if (!ensureMsgf(ActionClass, TEXT("Action class is not valid.")))
	{
		return;
	}

	UGP4_Action* NewAction = NewObject<UGP4_Action>(GetOwner(), ActionClass);
	for (const auto Action : Actions)
	{
		if (Action->ActionName == NewAction->ActionName)
		{
			UE_LOG(LogTemp, Log, TEXT("UGP4_ActionComponent::AddAction: Action %s already exists."),
			       *NewAction->ActionName.ToString());
			return;
		}
	}

	if (ensureMsgf(NewAction, TEXT("Failed to create action object.")))
	{
		NewAction->Init(this);
		Actions.Add(NewAction);
		if (NewAction->bAutoStart && ensure(NewAction->CanStart(Instigator)))
		{
			NewAction->StartAction(Instigator);
		}

		if (!bEquip)
			return;

		EquipAction(Instigator, NewAction);
	}
}

void UGP4_ActionComponent::RemoveAction(UGP4_Action* ActionToRemove, bool bShouldDestroy)
{
	if (!ensure(ActionToRemove && !ActionToRemove->IsRunning()))
	{
		UE_LOG(LogTemp, Log, TEXT("UGP4_ActionComponent::RemoveAction: Action is null or running, cannot remove."));
		return;
	}
	Actions.Remove(ActionToRemove);
	if (CurrentEquippedAction == ActionToRemove)
	{
		CurrentEquippedAction = nullptr;
		OnActionUnequipped.Broadcast(this, ActionToRemove, bShouldDestroy);
	}
}

bool UGP4_ActionComponent::HasAction(TSubclassOf<UGP4_Action> ActionClass) const
{
	for (UGP4_Action* Action : Actions)
	{
		if (Action && Action->GetClass() == ActionClass)
		{
			return true;
		}
	}
	return false;
}

bool UGP4_ActionComponent::StartActionByName(AActor* Instigator, FName ActionName, bool bDebug)
{
	for (UGP4_Action* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (!Action->CanStart(Instigator))
			{
				if (!bDebug)
					continue;

				FString FailedMsg = FString::Printf(TEXT("Failed to start action %s"), *ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
				continue;
			}

			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}

bool UGP4_ActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (UGP4_Action* Action : Actions)
	{
		if (!Action || Action->ActionName != ActionName)
			return false;

		if (!Action->IsRunning())
			return false;

		Action->StopAction(Instigator);
		return true;
	}
	return false;
}

void UGP4_ActionComponent::StartEquippedAction(AActor* Instigator)
{
	if (!CurrentEquippedAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGP4_ActionComponent::StartEquippedAction: No equipped action."));
		return;
	}
	StartActionByName(Instigator, CurrentEquippedAction->ActionName);
}

void UGP4_ActionComponent::StopEquippedAction(AActor* Instigator, bool bShouldBroadcastExecute)
{
	if (!CurrentEquippedAction)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGP4_ActionComponent::StopEquippedAction: No equipped action."));
		return;
	}
	if (bShouldBroadcastExecute)
		OnExecuteAction.Broadcast(this, CurrentEquippedAction, false);
	StopActionByName(Instigator, CurrentEquippedAction->ActionName);
}

void UGP4_ActionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentEquippedAction && CurrentEquippedAction->IsRunning() && CurrentEquippedAction->RequiresTick())
	{
		CurrentEquippedAction->Tick(DeltaTime);
	}
}
