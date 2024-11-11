#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GP4_ActionData.generated.h"

class UGP4_Action;

UCLASS()
class GP04_CATCHEM_SHEEP_API UGP4_ActionData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action Info")
	TSubclassOf<UGP4_Action> ActionClass{};

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("Actions", GetFName());
	}
};
