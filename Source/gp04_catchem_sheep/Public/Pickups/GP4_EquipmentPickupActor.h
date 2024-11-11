#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GP4_EquipmentPickupActor.generated.h"

//Def should pass self so spawner can test if it was spawned by player, and also should unsubscribe from the event
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteraction, AGP4_EquipmentPickupActor*, PickupActor);

class UGP4BaseInteractableComponent;
class UStaticMeshComponent;

UCLASS(Abstract)
class GP04_CATCHEM_SHEEP_API AGP4_EquipmentPickupActor : public AActor
{
	GENERATED_BODY()

public:
	AGP4_EquipmentPickupActor();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Pickup")
	float RespawnTime{10.0f};

	UPROPERTY(BlueprintCallable)
	FOnInteraction OnInteraction;
	
	/* If spawned by the player, we destroy the object upon interaction
	   otherwise we respawn in x seconds*/
	bool bWasSpawnedByPlayer{false};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UGP4BaseInteractableComponent* InteractableComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;
	
	//UPROPERTY(VisibleAnywhere)
	//USceneComponent* Root = nullptr;


	//Setters and Getters	
	UFUNCTION(BlueprintCallable)
	FName GetActionName() const { return ActionName; }

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Pickup", meta=(AllowPrivateAccess = "true"))
	FName ActionName{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Pickup", meta=(AllowPrivateAccess = "true"))
	FPrimaryAssetId ActionID{};
};
