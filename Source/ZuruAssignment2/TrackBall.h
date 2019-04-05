// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Engine/Classes/GameFramework/FloatingPawnMovement.h"
#include "Engine/Classes/Components/SphereComponent.h" 
#include "GlassBall.h"
#include "MyPlane.h"
#include "TrackBall.generated.h"

UCLASS()
class ZURUASSIGNMENT2_API ATrackBall : public APawn
{
	GENERATED_BODY()

public:
	ATrackBall();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	float time = 0;
	bool animateLight = false;
	AMyPlane* myPlane;
	bool sphereAlreadyGenerated = false;

	// camera controls
	UCameraComponent* OurCamera;
	void Orbit(float, float);
	float radius = 500;
	FVector2D mouseScreenLocationGrab;
	bool leftMouseDown = false;
	void OnMouseDown();
	void OnMouseUp();

	// pass keyboard commands to the GlassBall actor
	AGlassBall* myGlassBall; 
	void Move_XAxis(float);
	void Move_YAxis(float);
	void SetSphereSize(float);
	void SetRefractionIndex(float);
	void AnimateLight();
};
