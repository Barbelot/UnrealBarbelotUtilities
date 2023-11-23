
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<ABABoid> BoidClass;

	// Boids are spawned randomly around this object at distance below SpawnRadius.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Spawn")
	float SpawnRadius;

	// Number of boids to spawn. Recommended below 100.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Spawn", meta = (ClampMin = "0.0", ClampMax = "1000.0", UIMin = "0.0", UIMax = "1000.0"))
	float SpawnCount;

	// Target actor attracting boids, useful to avoid boids going too far away.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	AActor* Target;

	// Weight of the force towards the target compared to the other forces.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Target")
	float TargetWeight;

	// Strength of the catchup force that accelerate boids too far away from the target.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Target")
	float TargetCatchupStrength;

	// Radius of the catchup mechanism.
	// The catchup force is linearly interpolated between 0 and TargetCatchupStrength when the distance to the target go from MinRadius to MaxRadius.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Target")
	FVector2D targetCatchupRadiusMinMax;

	// Interpolate the position of the boids between their current position and the target position.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Target", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float SnapToTarget;

	// Speed range of the boids.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Boids")
	FVector2D SpeedMinMax;

	// Maximum turning speed of the boids.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Boids")
	float MaxSteerForce;

	// Only neighboring boids at a distance below the perception radius are considered for the boid movement.
	// 0 = infinite perception radius (recommended with low number of boids to avoid rotation jittering).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Boids")
	float PerceptionRadius;

	// Weight of the force enforcing alignment with neighboring boids, compared to the other forces.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Boids")
	float AlignmentWeight;

	// Weight of the force towards the neighboring boids center, compared to the other forces.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Boids")
	float CohesionWeight;

	// Weight of the force enforcing separation of neighboring boids, compared to the other forces.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Boids")
	float AvoidanceWeight;

	// Intensity of the noise added to the velocity direction.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Boids")
	float DirectionNoiseIntensity;

	// Frequency of the noise added to the velocity direction.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Boids")
	float DirectionNoiseFrequency;

	// Intensity of the noise added to the boid speed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Boids")
	float SpeedNoiseIntensity;

	// Frequency of the noise added to the boid speed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Boids")
	float SpeedNoiseFrequency;

	// Force of the wind, offsetting the boid positions every frame.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Wind")
	FVector WindForce;

	UFUNCTION(BlueprintCallable, Category = "Boids")
	void SpawnBoid();

	UFUNCTION(BlueprintCallable, Category = "Boids")
	void SpawnBoidAtPosition(FVector Position);

	UFUNCTION(BlueprintCallable, Category = "Boids")
	void RemoveBoid(int32 IndexToRemove = 0);
};
