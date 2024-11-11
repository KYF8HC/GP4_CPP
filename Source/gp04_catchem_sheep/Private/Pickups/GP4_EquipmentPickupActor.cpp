#include "Pickups/GP4_EquipmentPickupActor.h"
#include "InteractableSystem/GP4_BaseInteractableComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

AGP4_EquipmentPickupActor::AGP4_EquipmentPickupActor()
{
	//Root = CreateDefaultSubobject<USceneComponent>("Root");
	//RootComponent = Root;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	//StaticMesh->SetupAttachment(Root);

	InteractableComp = CreateDefaultSubobject<UGP4BaseInteractableComponent>(TEXT("InteractableComp"));
	InteractableComp->SetupAttachment(StaticMesh);
	
	InteractableComp->InteractableBoxTriggerRegion->SetupAttachment(InteractableComp);
	InteractableComp->InteractableSphereTriggerRegion->SetupAttachment(InteractableComp);

}
