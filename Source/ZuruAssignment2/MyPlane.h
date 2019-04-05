// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GlassBall.h"
#include "MyPlane.generated.h"

UCLASS()
class ZURUASSIGNMENT2_API AMyPlane : public AActor
{
	GENERATED_BODY()

public:
	AMyPlane();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


private:
	UStaticMeshComponent* Plane;

public:
	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
	TSubclassOf<AGlassBall> GlassBallBP;
	bool sphereAlreadyGenerated=false;

};