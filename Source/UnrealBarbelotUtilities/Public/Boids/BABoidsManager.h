
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BABoidsManager.generated.h"

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
