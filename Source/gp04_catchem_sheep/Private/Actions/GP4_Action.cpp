#include "Actions/GP4_Action.h"
#include "Components/GP4_ActionComponent.h"

void UGP4_Action::Init(UGP4_ActionComponent* NewActionComponent)
{
	OwningActionComponent = NewActionComponent;
	InitInternal();
}

void UGP4_Action::Tick_Implementation(float DeltaTime)
{
	
}

void UGP4_Action::StartAction_Implementation(AActor* Instigator)
{
	UGP4_ActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantsTags);

	bIsRunning = true;
	InstigatorActor = Instigator;
	
	TimeStarted = GetWorld()->GetTimeSeconds();
	GetOwningComponent()->OnActionStarted.Broadcast(GetOwningComponent(), this, false);
}

void UGP4_Action::StopAction_Implementation(AActor* Instigator)
{
	//ensureAlways(bIsRunning);

	UGP4_ActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);

	bIsRunning = false;
	InstigatorActor = Instigator;

	GetOwningComponent()->OnActionStopped.Broadcast(GetOwningComponent(), this, false);
	
	if(bIsOneTimeUse)
	{
		GetOwningComponent()->RemoveAction(this);
	}
}

bool UGP4_Action::CanStart_Implementation(AActor* Instigator) const
{
	if (IsRunning())
		return false;

	UGP4_ActionComponent* Comp = GetOwningComponent();
	if (Comp->ActiveGameplayTags.HasAny(BlockedTags))
		return false;
	return true;
}

UWorld* UGP4_Action::GetWorld() const
{
	//Outer is set when creating action via NewObject<T>
	if (AActor* Actor = Cast<AActor>(GetOuter()))
	{
		return Actor->GetWorld();
	}
	return nullptr;
}

UGP4_ActionComponent* UGP4_Action::GetOwningComponent() const
{
	return OwningActionComponent;
}

void UGP4_Action::InitInternal_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("UGP4_Action::InitInternal_Implementation: %s"), *ActionName.ToString());
}

