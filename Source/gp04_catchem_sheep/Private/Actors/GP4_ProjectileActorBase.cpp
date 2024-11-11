#include "Actors/GP4_ProjectileActorBase.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AGP4_ProjectileActorBase::AGP4_ProjectileActorBase()
{
	BoxComponentRef = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponentRef;
	
	MeshComponentRef = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponentRef->SetupAttachment(BoxComponentRef);

	ProjectileMovementComponentRef = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponentRef->InitialSpeed = 1000.0f;
	ProjectileMovementComponentRef->MaxSpeed = 1000.0f;
	ProjectileMovementComponentRef->bRotationFollowsVelocity = true;
	ProjectileMovementComponentRef->bShouldBounce = false;
}


