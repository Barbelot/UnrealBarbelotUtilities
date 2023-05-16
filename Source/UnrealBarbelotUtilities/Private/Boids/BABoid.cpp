
#include "Boids/BABoid.h"
#include "Boids/BABoidsManager.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABABoid::ABABoid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Set default values
	AdditionalVelocityDirection = FVector::ZeroVector;
	AdditionalVelocityIntensity = 0;

	//Create components
	StaticRootComponent = CreateDefaultSubobject<USceneComponent>("StaticRootComponent");
	StaticRootComponent->SetMobility(EComponentMobility::Static);
	RootComponent = StaticRootComponent;

	MovableRootComponent = CreateDefaultSubobject<USceneComponent>("MovableRootComponent");
	MovableRootComponent->SetupAttachment(RootComponent);
	MovableRootComponent->SetMobility(EComponentMobility::Movable);
}

void ABABoid::Initialize(FVector SpawnPosition, FRotator SpawnRotation)
{
	if (ensureMsgf(BoidsManager, TEXT("Boids Manager not set. This should never happen."))) {
		RandomValue = UKismetMathLibrary::RandomFloatInRange(0, 1);

		MovableRootComponent->SetRelativeLocation(SpawnPosition);
		MovableRootComponent->SetRelativeRotation(SpawnRotation);

		const float StartingSpeed = (BoidsManager->SpeedMinMax.X + BoidsManager->SpeedMinMax.Y) * 0.5f;
		Velocity = MovableRootComponent->GetForwardVector() * StartingSpeed;
	}
}

void ABABoid::UpdateBoid(float DeltaTime)
{
	//Wind applied directly as an offset on the boid
	MovableRootComponent->AddWorldOffset(BoidsManager->WindForce * DeltaTime);

	//Boid movement
	FVector Acceleration = FVector::ZeroVector;
	const FVector Position = MovableRootComponent->GetComponentLocation();

	//Move towards target
	if(BoidsManager->Target)
	{
		const FVector TargetPosition = BoidsManager->Target->GetActorLocation();
		const FVector OffsetToTarget = TargetPosition - Position;

		float TargetWeight = BoidsManager->TargetWeight;

		//Target catchup (accelerate when too far away)
		if(BoidsManager->TargetCatchupStrength > 0)
		{
			TargetWeight += UKismetMathLibrary::Lerp(0, BoidsManager->TargetCatchupStrength,
				UKismetMathLibrary::NormalizeToRange(OffsetToTarget.Length(),
					BoidsManager->targetCatchupRadiusMinMax.X, BoidsManager->targetCatchupRadiusMinMax.Y));
		}

		Acceleration = SteerTowards(OffsetToTarget) * TargetWeight;

	}

	//Boid forces
	if(NumPerceivedFlockmates > 0)
	{
		FlockCenter /= NumPerceivedFlockmates;

		const FVector AlignmentForce = SteerTowards(FlockDirection) * BoidsManager->AlignmentWeight;
		const FVector CohesionForce = SteerTowards(FlockCenter - Position) * BoidsManager->CohesionWeight;
		const FVector AvoidanceForce = SteerTowards(AvoidanceDirection) * BoidsManager->AvoidanceWeight;

		Acceleration += AlignmentForce;
		Acceleration += CohesionForce;
		Acceleration += AvoidanceForce;
	}

	//TODO : Add obstacles avoidance

	//Additional velocity
	if(AdditionalVelocityIntensity != 0 && AdditionalVelocityDirection.SquaredLength() > UE_SMALL_NUMBER)
	{
		Acceleration += SteerTowards(AdditionalVelocityDirection) * AdditionalVelocityIntensity;
	}

	//Update velocity from acceleration
	Velocity += Acceleration * DeltaTime;

	//Add velocity noise
	FVector NoiseValue;
	const float Time = GetWorld()->GetTimeSeconds();

	NoiseValue.X = UKismetMathLibrary::PerlinNoise1D(Time * BoidsManager->DirectionNoiseFrequency + RandomValue * 10);
	NoiseValue.Y = UKismetMathLibrary::PerlinNoise1D(Time * BoidsManager->DirectionNoiseFrequency + RandomValue * 100);
	NoiseValue.Z = UKismetMathLibrary::PerlinNoise1D(Time * BoidsManager->DirectionNoiseFrequency + RandomValue * 100);
	NoiseValue *= BoidsManager->DirectionNoiseIntensity;

	Velocity += NoiseValue;

	//Compute speed
	float Speed = Velocity.Length();
	const FVector Direction = Velocity / Speed;
	Speed = UKismetMathLibrary::Clamp(Speed, BoidsManager->SpeedMinMax.X, BoidsManager->SpeedMinMax.Y);

	//Add speed noise
	Speed += UKismetMathLibrary::PerlinNoise1D(Time * BoidsManager->SpeedNoiseFrequency + RandomValue * 10000) * BoidsManager->SpeedNoiseIntensity;

	//Update velocity from speed
	Velocity = Direction * Speed;

	//Move boid
	MovableRootComponent->AddWorldOffset(Velocity * DeltaTime);

	//Rotate boid
	MovableRootComponent->SetWorldRotation(Direction.Rotation());
}

FVector ABABoid::SteerTowards(FVector Direction) {

	FVector Output = Direction;
	Output.Normalize();
	Output = Output * BoidsManager->SpeedMinMax.Y - Velocity;

	return Output.GetClampedToMaxSize(BoidsManager->MaxSteerForce);
}

