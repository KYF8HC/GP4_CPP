#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GP4_ProjectileActorBase.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;

UCLASS()
class GP04_CATCHEM_SHEEP_API AGP4_ProjectileActorBase : public AActor
{
	GENERATED_BODY()

public:
	AGP4_ProjectileActorBase();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (ExposeOnSpawn = "true"))
	float ProjectileSpeed{ 0.0f };
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxComponentRef{};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MeshComponentRef{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponentRef{};
};
