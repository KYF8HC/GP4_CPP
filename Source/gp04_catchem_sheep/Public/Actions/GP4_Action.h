#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "GP4_Action.generated.h"

class UGP4_ActionComponent;

UCLASS(Blueprintable, Abstract)
class GP04_CATCHEM_SHEEP_API UGP4_Action : public UObject
{
	GENERATED_BODY()

public:
	/* Start immediately when added to an action component */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	bool bAutoStart{false};

	/* Action nickname to start/stop without a reference to the object */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	FName ActionName;
	
	/* Text displayed underneath Icons */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	FText TutorialText;
	
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsRunning() const noexcept { return bIsRunning; }

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool CanStart(AActor* Instigator) const;

	void Init(UGP4_ActionComponent* NewActionComponent);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
	void StopAction(AActor* Instigator);
	
	virtual UWorld* GetWorld() const override;
	virtual bool IsSupportedForNetworking() const override { return true; }

	bool RequiresTick() const noexcept { return bRequiresTick; }

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void Tick(float DeltaTime);
	
protected:

	UPROPERTY()
	float TimeStarted{0.0f};
	
	bool bIsRunning{false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	bool bIsOneTimeUse{false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action")
	bool bRequiresTick{false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSoftObjectPtr<UTexture2D> Icon{};
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AActor> InstigatorActor{};
	
	UPROPERTY()
	TObjectPtr<UGP4_ActionComponent> OwningActionComponent{};

	/* Tags added to OwningActor when activated, removed when action stops */
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantsTags{};

	/* Action can only start if OwningActor has none of these tags */
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlockedTags{};

	UFUNCTION(BlueprintCallable, Category = "Action")
	UGP4_ActionComponent* GetOwningComponent() const;

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void InitInternal();
};