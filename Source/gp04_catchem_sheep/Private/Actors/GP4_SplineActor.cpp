#include "Actors/GP4_SplineActor.h"

#include "Components/SplineComponent.h"


AGP4_SplineActor::AGP4_SplineActor()
{
	SplineComponentRef = CreateDefaultSubobject<USplineComponent>(TEXT("ProjectilePathSpline"));
	RootComponent = SplineComponentRef;

	ImpactPointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ImpactPointMesh"));
	ImpactPointMesh->SetupAttachment(RootComponent);	
}

void AGP4_SplineActor::DeleteSplineMeshComponent_Implementation(USplineMeshComponent* SplineMeshComponent)
{
}


USplineMeshComponent* AGP4_SplineActor::AddMeshComponent_Implementation(UStaticMesh* Mesh, UMaterial* Material)
{
	return nullptr;
}
