
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
	SpeedMultiplier = 1;

	//Create components
	StaticRootComponent = CreateDefaultSubobject<USceneComponent>("StaticRootComponent");
	StaticRootComponent->SetMobility(EComponentMobility::Static);
	RootComponent = StaticRootComponent;

	MovableRootComponent = CreateDefaultSubobject<USceneComponent>("MovableRootComponent");
	MovableRootComponent->SetupAttachment(RootComponent);
	MovableRootComponent->SetMobility(EComponentMobility::Movable);
}

void ABABoid::InitializeBoidFromPositionAndRotation(FVector SpawnPosition, FRotator SpawnRotation)
{
	MovableRootComponent->SetWorldLocation(SpawnPosition);
	MovableRootComponent->SetWorldRotation(SpawnRotation);

	InitializeBoid();
}

void ABABoid::InitializeBoid() 
{
	if (ensureMsgf(BoidsManager, TEXT("Boids Manager not set. This should never happen."))) {

		RandomValue = UKismetMathLibrary::RandomFloatInRange(0, 1);

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
	FVector TargetPosition = BoidsManager->TargetPosition;

	if(BoidsManager->Target)
	{
		TargetPosition = BoidsManager->Target->GetActorLocation();
	}

	const FVector TargetDirection = TargetPosition - Position;
	const float TargetDistance = TargetDirection.Length();

	float TargetWeight = BoidsManager->TargetWeight;

	//Target catchup (accelerate when too far away)
	if (BoidsManager->TargetCatchupStrength > 0)
	{
		TargetWeight += UKismetMathLibrary::Lerp(0, BoidsManager->TargetCatchupStrength,
			UKismetMathLibrary::NormalizeToRange(TargetDistance,
				BoidsManager->targetCatchupRadiusMinMax.X, BoidsManager->targetCatchupRadiusMinMax.Y));
	}

	//Target radius (reduce target attraction when getting too close)
	if (BoidsManager->TargetRadius > 0)
	{
		TargetWeight = UKismetMathLibrary::Lerp(0, TargetWeight,
			UKismetMathLibrary::NormalizeToRange(TargetDistance, 0, BoidsManager->TargetRadius));
	}

	Acceleration = SteerTowards(TargetDirection) * TargetWeight;

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

	NoiseValue.X = UKismetMathLibrary::PerlinNoise1D(Time * BoidsManager->DirectionNoiseFrequency + RandomValue * 7);
	NoiseValue.Y = UKismetMathLibrary::PerlinNoise1D(Time * BoidsManager->DirectionNoiseFrequency + RandomValue * 19);
	NoiseValue.Z = UKismetMathLibrary::PerlinNoise1D(Time * BoidsManager->DirectionNoiseFrequency + RandomValue * 37);
	NoiseValue *= BoidsManager->DirectionNoiseIntensity;

	Velocity += NoiseValue;

	//Compute speed
	float Speed = Velocity.Length();
	const FVector Direction = Velocity / Speed;
	Speed = UKismetMathLibrary::Clamp(Speed, BoidsManager->SpeedMinMax.X, BoidsManager->SpeedMinMax.Y) * SpeedMultiplier;

	//Add speed noise
	Speed += UKismetMathLibrary::PerlinNoise1D(Time * BoidsManager->SpeedNoiseFrequency + RandomValue * 1337) * BoidsManager->SpeedNoiseIntensity;

	//Update velocity from speed
	Velocity = Direction * Speed;

	//Move boid
	MovableRootComponent->AddWorldOffset(Velocity * DeltaTime);

	//Rotate boid
	MovableRootComponent->SetWorldRotation(Direction.Rotation());

	//Snap to target
	MovableRootComponent->SetWorldLocation(FMath::Lerp(MovableRootComponent->GetComponentLocation(), TargetPosition, BoidsManager->SnapToTarget));

	//AfterBoidUpdate event call
	AfterBoidUpdate();
}

FVector ABABoid::SteerTowards(FVector Direction) {

	FVector Output = Direction;
	Output.Normalize();
	Output = Output * BoidsManager->SpeedMinMax.Y - Velocity;

	return Output.GetClampedToMaxSize(BoidsManager->MaxSteerForce);
}

