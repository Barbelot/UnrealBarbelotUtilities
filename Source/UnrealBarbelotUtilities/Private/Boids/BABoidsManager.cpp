
#include "Boids/BABoidsManager.h"
#include "Boids/BABoid.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABABoidsManager::ABABoidsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set default values
	SpawnRadiusMinMax = FVector2D(500,1000);
	SpawnCount = 10;

	SpeedMinMax = FVector2D(200, 500);
	SpeedNoiseIntensity = 5.0f;
	SpeedNoiseFrequency = 1.0f;

	DirectionNoiseIntensity = 1.0f;
	DirectionNoiseFrequency = 1.0f;

	PerceptionRadius = 0;

	MaxSteerForce = 300;

	AlignmentWeight = 1;
	CohesionWeight = 1;
	AvoidanceWeight = 1;

	TargetWeight = 1;
	TargetRadius = 0;
	TargetCatchupStrength = 0;
	targetCatchupRadiusMinMax = FVector2D(200, 400);
	SnapToTarget = 0;

	WindForce = FVector::ZeroVector;
}

// Called when the game starts or when spawned
void ABABoidsManager::BeginPlay()
{
	Super::BeginPlay();

	//Initialize existing boids
	for (int i = 0; i < Boids.Num(); i++) {
		//TODO : Find a reliable way to handle null element in the list to avoid crashes
		if (IsValid(Boids[i])) {
			Boids[i]->BoidsManager = this;
			Boids[i]->InitializeBoid();
		}
	}

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

	UpdateBoids(DeltaTime);
}

void ABABoidsManager::SpawnBoid()
{
	if(!BoidClass)
	{
		return;
	}

	const FVector SpawnLocation = GetActorLocation() + UKismetMathLibrary::RandomUnitVector() * UKismetMathLibrary::RandomFloatInRange(SpawnRadiusMinMax.X, SpawnRadiusMinMax.Y);

	SpawnBoidAtPosition(SpawnLocation);
}

void ABABoidsManager::SpawnBoidAtPosition(FVector Position)
{
	if (!BoidClass)
	{
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	TObjectPtr<ABABoid> NewBoid = GetWorld()->SpawnActor<ABABoid>(BoidClass, GetActorLocation(), GetActorRotation(), SpawnParams);

	Boids.Add(NewBoid);

	NewBoid->BoidsManager = this;

	const FRotator SpawnRotation = UKismetMathLibrary::RandomRotator(true);

	NewBoid->InitializeBoidFromPositionAndRotation(Position, SpawnRotation);
}

void ABABoidsManager::RemoveBoid(int32 IndexToRemove)
{
	if (IndexToRemove >= 0 && Boids.Num() > IndexToRemove)
	{
		Boids[IndexToRemove]->Destroy();
		Boids.RemoveAt(IndexToRemove);
	}
}

void ABABoidsManager::UpdateBoids(float DeltaTime)
{
	if(Boids.Num() > 0)
	{
		int NumBoids = Boids.Num();

		//Initialize mean boids values to zero
		for(int i=0; i<NumBoids; i++)
		{
			Boids[i]->NumPerceivedFlockmates = 0;
			Boids[i]->FlockDirection = FVector::ZeroVector;
			Boids[i]->FlockCenter = FVector::ZeroVector;
			Boids[i]->AvoidanceDirection = FVector::ZeroVector;
		}

		//Compute mean boids values

		float SqrPerceptionRadius = PerceptionRadius * PerceptionRadius;

		for(int i=0; i<NumBoids; i++)
		{
			for(int j=0; j<NumBoids; j++)
			{
				if(i != j)
				{
					FVector OtherPosition = Boids[j]->MovableRootComponent->GetComponentLocation();
					FVector Distance = OtherPosition - Boids[i]->MovableRootComponent->GetComponentLocation();

					float SqrDist = Distance.X * Distance.X + Distance.Y * Distance.Y + Distance.Z * Distance.Z;

					if(PerceptionRadius == 0 || SqrDist < SqrPerceptionRadius)
					{
						Boids[i]->NumPerceivedFlockmates += 1;
						Boids[i]->FlockDirection += Boids[j]->MovableRootComponent->GetForwardVector();
						Boids[i]->FlockCenter += OtherPosition;

						if (SqrDist > 0) {
							Boids[i]->AvoidanceDirection -= (Distance / SqrDist);
						}
					}
				}
			}
		}

		for(int i=0; i<NumBoids; i++)
		{
			Boids[i]->UpdateBoid(DeltaTime);
		}
	}
}
