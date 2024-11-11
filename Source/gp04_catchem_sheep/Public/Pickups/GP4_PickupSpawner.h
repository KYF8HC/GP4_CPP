#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GP4_PickupSpawner.generated.h"

class AGP4_PlayerCharacter;
class AGP4_EquipmentPickupActor;

USTRUCT(BlueprintType)
struct FPickupInfoRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ActionName{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPrimaryAssetId PickupID{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FVector> SpawnLocations{};
};

UCLASS(Abstract)
class GP04_CATCHEM_SHEEP_API AGP4_PickupSpawner : public AActor
{
	GENERATED_BODY()

public:
	AGP4_PickupSpawner();
	/* Spawns multiple pickup actors */
	void OnAssetLoaded(FPrimaryAssetId LoadedID, TArray<FVector> SpawnLocations);

	/* Spawns a single pickup actor */
	void OnAssetLoaded(FPrimaryAssetId LoadedID, FVector SpawnLocation);
	
	UFUNCTION()
	void OnPickupInteracted(AGP4_EquipmentPickupActor* PickupActor);

	UFUNCTION()
	void SpawnPickupByActionNameAndLocation(FName ActionName, FVector SpawnLocation);

	UFUNCTION()
	void SpawnInitialPickups();

private:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Pickups", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UDataTable> PickupDataTable{};
	
	UPROPERTY(VisibleAnywhere, Category= "Pickups", meta=(AllowPrivateAccess = "true"))
	TArray<TObjectPtr<AGP4_EquipmentPickupActor>> InitiallySpawnedPickups{};

	UPROPERTY(VisibleAnywhere, Category= "Pickups", meta=(AllowPrivateAccess = "true"))
	TArray<TObjectPtr<AGP4_EquipmentPickupActor>> PlayerSpawnedPickups{};

	UPROPERTY()
	TArray<FTimerHandle> PickupRespawnTimers{};
	
};