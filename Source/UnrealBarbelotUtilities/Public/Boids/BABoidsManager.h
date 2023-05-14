
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

	TArray<ABABoid*> Boids;

	void UpdateBoids();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Spawn")
	TSubclassOf<ABABoid> BoidClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Spawn")
	float SpawnRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Spawn")
	float SpawnCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boids|Target")
	AActor* Target;

	UFUNCTION(BlueprintCallable, Category = "Boids")
	void SpawnBoid();

	UFUNCTION(BlueprintCallable, Category = "Boids")
	void RemoveBoid(int IndexToRemove = 0);
};
