#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GP4_PickupData.generated.h"

class AGP4_EquipmentPickupActor;

UCLASS()
class GP04_CATCHEM_SHEEP_API UGP4_PickupData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Info")
	TSubclassOf<AGP4_EquipmentPickupActor> PickupClass{};

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("Pickups", GetFName());
	}
};
