#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "GlassBall.generated.h"

UCLASS()
class ZURUASSIGNMENT2_API AGlassBall : public AActor
{
	GENERATED_BODY()
	
public:	
	AGlassBall();
	FVector lightPos = FVector(0., 300, 300);
	FVector spherePos = FVector(0., 0., 30);
	float sphereRadius = 30.;
	float GlassRefractionIndex = 1.12;
	UMaterialInstanceDynamic *material;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
