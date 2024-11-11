#pragma once

#include "CoreMinimal.h"
#include "GP4_Action.h"
#include "GP4_ProjectileAction.generated.h"

class AGP4_ProjectileActorBase;
class AGP4_SplineActor;
class AGP4_PlayerCharacter;

UCLASS()
class GP04_CATCHEM_SHEEP_API UGP4_ProjectileAction : public UGP4_Action
{
	GENERATED_BODY()

public:
	virtual void Tick_Implementation(float DeltaTime) override;
	virtual void StartAction_Implementation(AActor* Instigator) override;
	virtual void StopAction_Implementation(AActor* Instigator) override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
	void ExecuteAction(AActor* Instigator);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Action", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGP4_ProjectileActorBase> ProjectileClass{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Action", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGP4_SplineActor> SplineClass{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AGP4_SplineActor> SplineActorRef{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Action",
		meta = (AllowPrivateAccess = "true"))
	float ProjectileSpeed{0.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Action",
		meta = (AllowPrivateAccess = "true", ClampMin = "2000.0", UIMin = "2000.0"))
	float MaxProjectileSpeed{3000.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Action",
		meta = (AllowPrivateAccess = "true", ClampMin = "1500.0", UIMin = "1500.0"))
	float MinProjectileSpeed{1500.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile Action", meta = (AllowPrivateAccess = "true"))
	bool bShouldIncrease{true};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Action", meta = (AllowPrivateAccess = "true"))
	float ProjectileSpeedChangeRate{100.0f};
};
