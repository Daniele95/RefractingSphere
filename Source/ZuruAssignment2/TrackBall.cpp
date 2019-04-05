#include "TrackBall.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Classes/Components/InputComponent.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "Engine/Classes/Engine/Engine.h"
#include "math.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"

ATrackBall::ATrackBall()
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetAbsolute(true, true, false);
	OurCamera->SetWorldLocation(FVector(radius, 0., 200.));
	OurCamera->SetWorldRotation(FRotator(0., 180., 0.));
}

void ATrackBall::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AMyPlane> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		myPlane = *ActorItr;
	
}

void ATrackBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// check if sphere is already been generated
	if(!sphereAlreadyGenerated) {
		sphereAlreadyGenerated = myPlane->sphereAlreadyGenerated;
		for (TActorIterator<AGlassBall> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			myGlassBall = *ActorItr;
	}
	// handle mouse control
	if (Controller)
	{
		APlayerController* playerController = Cast<APlayerController>(GetController());
		if (playerController != nullptr)
		{
			FVector2D mouseLocation;
			if (playerController->GetMousePosition(mouseLocation.X, mouseLocation.Y))
			{
				int32 screenWidth = 0;
				int32 screenHeight = 0;
				playerController->GetViewportSize(screenWidth, screenHeight);
				if (leftMouseDown)
					Orbit((mouseScreenLocationGrab.X - mouseLocation.X) / screenWidth,
					(mouseScreenLocationGrab.Y - mouseLocation.Y) / screenHeight);

			}
		}
	}
	// handle light animation
	float elapsed = UGameplayStatics::GetRealTimeSeconds(GetWorld()) - time;
	if(myGlassBall) {
		if (animateLight && elapsed<8 ) {
			myGlassBall->lightPos.X = 500.*cos(elapsed);
			myGlassBall->lightPos.Y = 500.*sin(elapsed);
			myGlassBall->lightPos.Z = 300.;
		}
		else {
			animateLight = 0.;
		}
	}
}

void ATrackBall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(InputComponent);

	InputComponent->BindAction("LeftMouseDown", IE_Pressed, this, &ATrackBall::OnMouseDown);
	InputComponent->BindAction("LeftMouseDown", IE_Released, this, &ATrackBall::OnMouseUp);

	InputComponent->BindAction("AnimateLight", IE_Released, this, &ATrackBall::AnimateLight);

	InputComponent->BindAxis("MoveForward", this, &ATrackBall::Move_XAxis);
	InputComponent->BindAxis("MoveRight", this, &ATrackBall::Move_YAxis);

	InputComponent->BindAxis("BallSize", this, &ATrackBall::SetSphereSize);
	
	InputComponent->BindAxis("RefractionIndex", this, &ATrackBall::SetRefractionIndex);

}


void ATrackBall::Move_XAxis(float AxisValue)
{
	if (myGlassBall) {
		myGlassBall->spherePos.X = myGlassBall->spherePos.X + AxisValue;
	}
}

void ATrackBall::Move_YAxis(float AxisValue)
{
	if (myGlassBall) {
		myGlassBall->spherePos.Y = myGlassBall->spherePos.Y - AxisValue;
	}

}

void ATrackBall::AnimateLight()
{
	time = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	animateLight = true;
}

void ATrackBall::SetSphereSize(float size)
{
	if (myGlassBall) {
		myGlassBall->spherePos.Z = myGlassBall->spherePos.Z + size;
		myGlassBall->sphereRadius = myGlassBall->sphereRadius + size;
	}
}

void ATrackBall::SetRefractionIndex(float index)
{
	if(myGlassBall) {
	myGlassBall->GlassRefractionIndex = myGlassBall->GlassRefractionIndex + index * .001;
	if (myGlassBall->GlassRefractionIndex < 1) myGlassBall->GlassRefractionIndex = 1.;
	}
}

void ATrackBall::Orbit(const float magnitudeX, const float magnitudeY)
{
	if (magnitudeX != 0 && Controller)
	{
		APlayerController* playerController = Cast<APlayerController>(GetController());
		if (playerController != nullptr)
		{
			float phi = (magnitudeX - .5)  *6.28;
			float theta = (magnitudeY + .5)  *3.14;
			FVector newPos = FVector(radius*cos(theta)*cos(phi), radius*cos(theta)*sin(phi), radius*sin(theta));
			OurCamera->SetWorldLocation(newPos);
			FRotator newRot = FRotator(-theta / 3.14 * 180, phi / 3.14 * 180 + 180, 0.);
			OurCamera->SetWorldRotation(newRot);
		}
	}
}

void ATrackBall::OnMouseDown() {
	leftMouseDown = true;
}

void ATrackBall::OnMouseUp() {
	leftMouseDown = false;
}
