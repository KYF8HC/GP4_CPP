#include "Pickups/GP4_PickupSpawner.h"
#include "DataAssets/GP4_PickupData.h"
#include "Engine/AssetManager.h"
#include "Pickups/GP4_EquipmentPickupActor.h"


AGP4_PickupSpawner::AGP4_PickupSpawner()
{
	
}

void AGP4_PickupSpawner::OnAssetLoaded(FPrimaryAssetId LoadedID, TArray<FVector> SpawnLocations)
{
	UAssetManager* AssetManager = UAssetManager::GetIfInitialized();
	if (!AssetManager)
	{
		UE_LOG(LogTemp, Error, TEXT("AGP4_PickupSpawner::OnAssetLoaded: AssetManager is nullptr"));
		return;
	}

	const UGP4_PickupData* PickupData = Cast<UGP4_PickupData>(AssetManager->GetPrimaryAssetObject(LoadedID));
	if (!PickupData)
	{
		UE_LOG(LogTemp, Error, TEXT("AGP4_PickupSpawner::OnAssetLoaded: PickupData is nullptr"));
		return;
	}

	for (const FVector& SpawnLocation : SpawnLocations)
	{
		AGP4_EquipmentPickupActor* PickupActor = GetWorld()->SpawnActor<AGP4_EquipmentPickupActor>(
			PickupData->PickupClass, SpawnLocation, GetActorRotation());

		InitiallySpawnedPickups.Add(PickupActor);
		PickupActor->OnInteraction.AddDynamic(this, &AGP4_PickupSpawner::OnPickupInteracted);

		PickupActor->bWasSpawnedByPlayer = false;
	}
}

void AGP4_PickupSpawner::OnAssetLoaded(FPrimaryAssetId LoadedID, FVector SpawnLocation)
{
	UAssetManager* AssetManager = UAssetManager::GetIfInitialized();
	if (!AssetManager)
	{
		UE_LOG(LogTemp, Error, TEXT("AGP4_PickupSpawner::OnAssetLoaded: AssetManager is nullptr"));
		return;
	}

	const UGP4_PickupData* PickupData = Cast<UGP4_PickupData>(AssetManager->GetPrimaryAssetObject(LoadedID));
	if (!PickupData)
	{
		UE_LOG(LogTemp, Error, TEXT("AGP4_PickupSpawner::OnAssetLoaded: PickupData is nullptr"));
		return;
	}

	AGP4_EquipmentPickupActor* PickupActor = GetWorld()->SpawnActor<AGP4_EquipmentPickupActor>(
			PickupData->PickupClass, SpawnLocation, GetActorRotation());

	InitiallySpawnedPickups.Add(PickupActor);
	PickupActor->OnInteraction.AddDynamic(this, &AGP4_PickupSpawner::OnPickupInteracted);
	PickupActor->bWasSpawnedByPlayer = false;
}

void AGP4_PickupSpawner::OnPickupInteracted(AGP4_EquipmentPickupActor* PickupActor)
{
	for (auto Pickup : InitiallySpawnedPickups)
	{
		if (Pickup == PickupActor)
		{
			PickupActor->OnInteraction.RemoveDynamic(this, &AGP4_PickupSpawner::OnPickupInteracted);
			
			//Start timer to respawn
			FTimerHandle TimerHandle;			
			
			FTimerDelegate Delegate;
			Delegate.BindUFunction(this, FName("SpawnPickupByActionNameAndLocation"), PickupActor->GetActionName(), PickupActor->GetActorLocation());
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, PickupActor->RespawnTime, false);

			InitiallySpawnedPickups.Remove(Pickup);
			break;
		}
	}
}

void AGP4_PickupSpawner::SpawnPickupByActionNameAndLocation(FName ActionName, FVector SpawnLocation)
{
	TArray<FPickupInfoRow*> Rows;
	if (PickupDataTable)
		PickupDataTable->GetAllRows("", Rows);

	for (auto Row : Rows)
	{
		if (Row->ActionName != ActionName)
			continue;

		UAssetManager* AssetManager = UAssetManager::GetIfInitialized();
		if (!AssetManager)
		{
			UE_LOG(LogTemp, Error, TEXT("AssetManager is nullptr"));
			return;
		}

		TArray<FName> Bundles;
		FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(
			this, &AGP4_PickupSpawner::OnAssetLoaded, Row->PickupID, SpawnLocation);
		AssetManager->LoadPrimaryAsset(Row->PickupID, Bundles, Delegate);
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("AGP4_PickupSpawner::SpawnPickupByActionNameAndLocation: Not implemented"));
}


void AGP4_PickupSpawner::SpawnInitialPickups()
{
	TArray<FPickupInfoRow*> Rows;
	PickupDataTable->GetAllRows("", Rows);

	for (auto Row : Rows)
	{
		UAssetManager* AssetManager = UAssetManager::GetIfInitialized();
		if (!AssetManager)
		{
			UE_LOG(LogTemp, Error, TEXT("AssetManager is nullptr"));
			return;
		}

		TArray<FName> Bundles;
		FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(
			this, &AGP4_PickupSpawner::OnAssetLoaded, Row->PickupID, Row->SpawnLocations);
		AssetManager->LoadPrimaryAsset(Row->PickupID, Bundles, Delegate);
	}
}
