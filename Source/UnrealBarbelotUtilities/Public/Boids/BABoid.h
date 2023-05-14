// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BABoid.generated.h"

class USceneComponent;
class ABABoidsManager;

UCLASS()
class UNREALBARBELOTUTILITIES_API ABABoid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABABoid();

protected:

	float RandomValue;

public:	

	/*** VARIABLES ***/

	//Component moved by the boid movement
	UPROPERTY(VisibleAnywhere, Category = "Boids")
	TObjectPtr<USceneComponent> MovableRootComponent;

	//Component not moved by the boid movement
	UPROPERTY(VisibleAnywhere, Category = "Boids")
	TObjectPtr<USceneComponent> StaticRootComponent;

	UPROPERTY(VisibleAnywhere, Category = "Boids")
	TObjectPtr<ABABoidsManager> BoidsManager;

	//Boid state
	UPROPERTY(VisibleAnywhere, Category = "Boids")
	int Id;

	UPROPERTY()
	FVector Velocity;

	//Additional velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids")
	FVector AdditionalVelocityDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids")
	float AdditionalVelocityIntensity;

	//Flock parameters
	UPROPERTY(VisibleAnywhere, Category = "Boids")
	FVector FlockDirection;

	UPROPERTY(VisibleAnywhere, Category = "Boids")
	FVector AvoidanceDirection;

	UPROPERTY(VisibleAnywhere, Category = "Boids")
	FVector CenterOfFlockmates;

	UPROPERTY(VisibleAnywhere, Category = "Boids")
	int NumPerceivedFlockmates;

	/*** METHODS ***/

	UFUNCTION()
	void Initialize(FVector SpawnPosition, FRotator SpawnRotation);

	UFUNCTION()
	void UpdateBoid();
};
