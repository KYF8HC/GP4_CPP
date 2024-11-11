#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "GP4_ActionComponent.generated.h"

class AGP4_PickupSpawner;
class UGP4_Action;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActionStateChanged, UGP4_ActionComponent*, OwningComponent,
                                             UGP4_Action*, Action, bool, bShouldDestroy);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GP04_CATCHEM_SHEEP_API UGP4_ActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGP4_ActionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags{};

	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionStarted;

	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionStopped;

	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnExecuteAction;

	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionEquipped;

	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionUnequipped;

	UFUNCTION(BlueprintCallable, Category = "Action")
	void AddAction(AActor* Instigator, TSubclassOf<UGP4_Action> ActionClass, bool bEquip = false);

	UFUNCTION(BlueprintCallable, Category = "Action")
	void RemoveAction(UGP4_Action* ActionToRemove, bool bShouldDestroy = false);
	
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool HasAction(TSubclassOf<UGP4_Action> ActionClass) const;

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool StartActionByName(AActor* Instigator, FName ActionName, bool bDebug = false);

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool StopActionByName(AActor* Instigator, FName ActionName);
	
	void StartEquippedAction(AActor* Instigator);
	void StopEquippedAction(AActor* Instigator, bool bShouldBroadcastExecute = false);
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;
	
	//Setters and Getters
	UFUNCTION(BlueprintCallable, Category = "Action")
	UGP4_Action* FindActionByName(FName ActionName) const;
	TArray<TObjectPtr<UGP4_Action>> GetActions() const noexcept { return Actions; }
	UGP4_Action* GetCurrentEquippedAction() const noexcept { return CurrentEquippedAction.Get(); }
	
	void SetPickupSpawner(AGP4_PickupSpawner* NewPickupSpawner) { PickupSpawnerRef = NewPickupSpawner; }
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actions")
	TArray<TSubclassOf<UGP4_Action>> DefaultActions{};

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<UGP4_Action>> Actions{};

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UGP4_Action> CurrentEquippedAction{};

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AGP4_PickupSpawner> PickupSpawnerRef{};

	virtual void BeginPlay() override;
	void EquipAction(AActor* Instigator, UGP4_Action* NewAction);
	
	
};
