
#include "Boids/BABoidsManager.h"

// Sets default values
ABABoidsManager::ABABoidsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABABoidsManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABABoidsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

