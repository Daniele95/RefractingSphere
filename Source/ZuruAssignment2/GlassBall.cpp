#include "GlassBall.h"

AGlassBall::AGlassBall()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGlassBall::BeginPlay()
{
	Super::BeginPlay();
}

void AGlassBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (material) {
		material->SetScalarParameterValue(FName("GlassRefractionIndez"), GlassRefractionIndex);
		material->SetScalarParameterValue(FName("sphereRadius"), sphereRadius);
		material->SetVectorParameterValue(FName("spherePos"), spherePos);
		material->SetVectorParameterValue(FName("lightPos"), lightPos);
	}
}

