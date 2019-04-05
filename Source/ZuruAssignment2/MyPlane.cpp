#include "MyPlane.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "ConstructorHelpers.h"

// constructor sets plane into blueprint
AMyPlane::AMyPlane()
{
	Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneAsset(TEXT("/Game/plane"));
	if (PlaneAsset.Succeeded()) Plane->SetStaticMesh(PlaneAsset.Object);
}

// on beginPlay the plane is converted to an instance and passed 
// as a parameter to a new GlassBall actor
void AMyPlane::BeginPlay()
{
	Super::BeginPlay();
	UMaterialInstanceDynamic* DynamicMatInstance = Plane->CreateAndSetMaterialInstanceDynamic(0);

	if (GlassBallBP) {
		FActorSpawnParameters SpawnParams;
		AGlassBall* myGlassBall = GetWorld()->SpawnActor<AGlassBall>(GlassBallBP, GetTransform(), SpawnParams);
		myGlassBall->material = DynamicMatInstance;
	}
}

void AMyPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
