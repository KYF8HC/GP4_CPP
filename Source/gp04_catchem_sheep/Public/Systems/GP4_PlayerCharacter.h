#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GP4_PlayerCharacter.generated.h"

struct FGameplayTag;
class AGP4_PickupSpawner;
class UGP4_ActionComponent;
class UCameraComponent;
class USpringArmComponent;
class UGP4ObjectInteractorComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnThrow);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAim);

UCLASS(Abstract)
class GP04_CATCHEM_SHEEP_API AGP4_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGP4_PlayerCharacter();

	UPROPERTY(BlueprintAssignable)
	FOnThrow OnThrow;

	UPROPERTY(BlueprintAssignable)
	FOnAim OnAim;

	UPROPERTY(BlueprintAssignable)
	FOnAim OnStopAim;

#pragma region Input handling
	void HandleMove(FVector2D Input);
	void HandleLook(FVector2D Input);
	void HandleUseItem();
	void HandleStopItem();
	void HandleExecuteAction();
	void StopMovement();
	void SetUseControllerRotation(bool bShouldUse);

	UFUNCTION(BlueprintCallable)
	void SetReceiveInput(bool bShouldReceive) { bShouldReceiveInput = bShouldReceive; }
#pragma endregion

	UFUNCTION(BlueprintNativeEvent)
	void InitializePlayer();
	
	//Setters and Getters
	void SetPickupSpawner(AGP4_PickupSpawner* Spawner) const;
	UCameraComponent* GetCameraComponent() const noexcept { return CameraComponentRef.Get(); }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interactor", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGP4ObjectInteractorComponent> ObjectInteractor{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponentRef{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponentRef{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actions", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGP4_ActionComponent> ActionComponentRef{};
	
	UPROPERTY()
	TObjectPtr<AGP4_PickupSpawner> PickupSpawnerRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tags", meta = (AllowPrivateAccess = "true"))
	FName PlayerTag{"Player"};

	UPROPERTY(BlueprintReadOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	bool bShouldReceiveInput{true};
};