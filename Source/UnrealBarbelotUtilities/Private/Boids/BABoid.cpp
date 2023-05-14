// Fill out your copyright notice in the Description page of Project Settings.


#include "Boids/BABoid.h"
#include "Boids/BABoidsManager.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABABoid::ABABoid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticRootComponent = CreateDefaultSubobject<USceneComponent>("StaticRootComponent");
	StaticRootComponent->SetMobility(EComponentMobility::Static);
	RootComponent = StaticRootComponent;

	MovableRootComponent = CreateDefaultSubobject<USceneComponent>("MovableRootComponent");
	MovableRootComponent->SetupAttachment(RootComponent);
	MovableRootComponent->SetMobility(EComponentMobility::Movable);
}

void ABABoid::Initialize(FVector SpawnPosition, FRotator SpawnRotation)
{
	if (ensureMsgf(BoidsManager, TEXT("Boids Manager not set. This should never happen."))) {
		RandomValue = UKismetMathLibrary::RandomFloatInRange(0, 1);

		MovableRootComponent->SetRelativeLocation(SpawnPosition);
		MovableRootComponent->SetRelativeRotation(SpawnRotation);

		const float StartingSpeed = (BoidsManager->MinSpeed + BoidsManager->MaxSpeed) * 0.5f;
		Velocity = MovableRootComponent->GetForwardVector() * StartingSpeed;
	}
}

void ABABoid::UpdateBoid()
{

}

