
#include "Boids/BABoidsManager.h"
#include "Boids/BABoid.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABABoidsManager::ABABoidsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set default values
	SpawnRadius = 1000;
	SpawnCount = 10;

	SpeedMinMax = FVector2D(200, 500);
	SpeedNoiseIntensity = 0;
	SpeedNoiseFrequency = 1.0f;

	DirectionNoiseIntensity = 0;
	DirectionNoiseFrequency = 5.0f;

	PerceptionRadius = 0;

	MaxSteerForce = 300;

	AlignmentWeight = 1;
	CohesionWeight = 1;
	AvoidanceWeight = 1;

	TargetWeight = 1;
	TargetCatchupStrength = 0;
	targetCatchupRadiusMinMax = FVector2D(200, 400);

	WindForce = FVector::ZeroVector;
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

	UpdateBoids(DeltaTime);
}

void ABABoidsManager::SpawnBoid()
{
	if(!BoidClass)
	{
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	TObjectPtr<ABABoid> NewBoid = GetWorld()->SpawnActor<ABABoid>(BoidClass, GetActorLocation(), GetActorRotation(), SpawnParams);

	Boids.Add(NewBoid);

	NewBoid->BoidsManager = this;

	const FVector SpawnLocation = GetActorLocation() + UKismetMathLibrary::RandomUnitVector() * UKismetMathLibrary::RandomFloatInRange(0, SpawnRadius);
	const FRotator SpawnRotation = UKismetMathLibrary::RandomRotator(true);

	NewBoid->Initialize(SpawnLocation, SpawnRotation);
}

void ABABoidsManager::RemoveBoid(int IndexToRemove)
{
	if (Boids.Num() > IndexToRemove)
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
						Boids[i]->AvoidanceDirection -= (Distance / SqrDist);
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
