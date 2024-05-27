
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boids")
	TObjectPtr<USceneComponent> MovableRootComponent;

	//Component not moved by the boid movement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boids")
	TObjectPtr<USceneComponent> StaticRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boids")
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

	//Speed multiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids")
	float SpeedMultiplier;

	//Flock parameters
	UPROPERTY(VisibleAnywhere, Category = "Boids")
	FVector FlockDirection;

	UPROPERTY(VisibleAnywhere, Category = "Boids")
	FVector AvoidanceDirection;

	UPROPERTY(VisibleAnywhere, Category = "Boids")
	FVector FlockCenter;

	UPROPERTY(VisibleAnywhere, Category = "Boids")
	int NumPerceivedFlockmates;

	/*** METHODS ***/

	UFUNCTION()
	void InitializeBoidFromPositionAndRotation(FVector SpawnPosition, FRotator SpawnRotation);

	UFUNCTION()
	void InitializeBoid();

	UFUNCTION()
	void UpdateBoid(float DeltaTime);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "AfterBoidUpdate"))
	void AfterBoidUpdate();

	FVector SteerTowards(FVector direction);
};
