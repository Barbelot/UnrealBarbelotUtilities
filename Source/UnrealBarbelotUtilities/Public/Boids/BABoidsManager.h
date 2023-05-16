
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BABoidsManager.generated.h"

class ABABoid;

UCLASS(hideCategories = (Rendering, Physics, LOD, Activation, Input, Replication, Collision, Actor, Cooking, HLOD, Networking))
class UNREALBARBELOTUTILITIES_API ABABoidsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABABoidsManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<TObjectPtr<ABABoid>> Boids;

	void UpdateBoids(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Spawn")
	TSubclassOf<ABABoid> BoidClass;

	// Boids are spawned randomly around this object at distance below SpawnRadius.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Spawn")
	float SpawnRadius;

	// Number of boids to spawn. Recommended below 100.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Spawn", meta = (ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))
	float SpawnCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Target")
	AActor* Target;

	// Weight of the force towards the target compared to the other forces.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Target")
	float TargetWeight;

	// Strength of the catchup force that accelerate boids too far away from the target.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Target")
	float TargetCatchupStrength;

	// Radius of the catchup mechanism.
	// The catchup force is linearly interpolated between 0 and TargetCatchupStrength when the distance to the target go from MinRadius to MaxRadius.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Target")
	FVector2D targetCatchupRadiusMinMax;

	// Speed range of the boids.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Boid")
	FVector2D SpeedMinMax;

	// Maximum turning speed of the boids.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Boid")
	float MaxSteerForce;

	// Only neighboring boids at a distance below the perception radius are considered for the boid movement.
	// 0 = infinite perception radius (recommended with low number of boids to avoid rotation jittering).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Boid")
	float PerceptionRadius;

	// Weight of the force enforcing alignment with neighboring boids, compared to the other forces.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Boid")
	float AlignmentWeight;

	// Weight of the force towards the neighboring boids center, compared to the other forces.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Boid")
	float CohesionWeight;

	// Weight of the force enforcing separation of neighboring boids, compared to the other forces.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Boid")
	float AvoidanceWeight;

	// Intensity of the noise added to the velocity direction.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Boid")
	float DirectionNoiseIntensity;

	// Frequency of the noise added to the velocity direction.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Boid")
	float DirectionNoiseFrequency;

	// Intensity of the noise added to the boid speed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Boid")
	float SpeedNoiseIntensity;

	// Frequency of the noise added to the boid speed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Boid")
	float SpeedNoiseFrequency;

	// Force of the wind, offsetting the boid positions every frame.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Wind")
	FVector WindForce;

	UFUNCTION(BlueprintCallable, Category = "Boids")
	void SpawnBoid();

	UFUNCTION(BlueprintCallable, Category = "Boids")
	void RemoveBoid(int IndexToRemove = 0);
};
