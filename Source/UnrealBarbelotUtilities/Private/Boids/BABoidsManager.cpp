
#include "Boids/BABoidsManager.h"
#include "Boids/BABoid.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABABoidsManager::ABABoidsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnRadius = 1000;
	SpawnCount = 10;
}

// Called when the game starts or when spawned
void ABABoidsManager::BeginPlay()
{
	Super::BeginPlay();

	//Spawn boids
	for(int i=0; i<SpawnCount; i++)
	{
		SpawnBoid();
	}
}

// Called every frame
void ABABoidsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateBoids();
}

void ABABoidsManager::SpawnBoid()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FVector SpawnLocation = GetActorLocation() + UKismetMathLibrary::RandomUnitVector() * UKismetMathLibrary::RandomFloatInRange(0, SpawnRadius);
	const FRotator SpawnRotation = UKismetMathLibrary::RandomRotator(true);

	ABABoid* NewBoid = GetWorld()->SpawnActor<ABABoid>(BoidClass, SpawnLocation, SpawnRotation, SpawnParams);

	Boids.Add(NewBoid);
}

void ABABoidsManager::RemoveBoid(int IndexToRemove)
{
	if (Boids.Num() > IndexToRemove)
	{
		Boids[IndexToRemove]->Destroy();
		Boids.RemoveAt(IndexToRemove);
	}
}

void ABABoidsManager::UpdateBoids()
{
	if(Boids.Num() > 0)
	{
		
	}
}
