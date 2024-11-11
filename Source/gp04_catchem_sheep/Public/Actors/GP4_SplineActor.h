#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GP4_SplineActor.generated.h"

class USplineMeshComponent;
class USplineComponent;

UCLASS()
class GP04_CATCHEM_SHEEP_API AGP4_SplineActor : public AActor
{
	GENERATED_BODY()

public:
	AGP4_SplineActor();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Spline")
	USplineMeshComponent* AddMeshComponent(UStaticMesh* Mesh, UMaterial* Material);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Spline")
	void DeleteSplineMeshComponent(USplineMeshComponent* SplineMeshComponent);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USplineComponent> SplineComponentRef{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> ImpactPointMesh{};
};
