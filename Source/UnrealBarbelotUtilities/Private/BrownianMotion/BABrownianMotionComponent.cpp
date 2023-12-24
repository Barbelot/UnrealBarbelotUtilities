
#include "BrownianMotion/BABrownianMotionComponent.h"

// Sets default values for this component's properties
UBABrownianMotionComponent::UBABrownianMotionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Default values
	bEnableMotion = true;
	AxisAmplitude = FVector::OneVector;
	Amplitude = 100;
	Frequency = 0.5f;
	TimeOffset = 0;
	bRandomizeTimeOffset = true;
	PositionOffset = FVector::ZeroVector;
}


// Called when the game starts
void UBABrownianMotionComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get Starting position
	StartingPosition = GetOwner()->GetRootComponent()->GetRelativeLocation();

	if (bRandomizeTimeOffset)
	{
		TimeOffset += FMath::RandRange(-10000, 0);
	}
}

// Called every frame
void UBABrownianMotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Apply Brownian Motion
	if (bEnableMotion) {
		FVector NewLocation = GetPerlinNoise3D(GetWorld()->GetTimeSeconds() + TimeOffset, Frequency);
		NewLocation *= AxisAmplitude * Amplitude;
		NewLocation += StartingPosition + PositionOffset;
		GetOwner()->SetActorRelativeLocation(NewLocation);
	}
}

// Get 3D perlin noise vector
FVector UBABrownianMotionComponent::GetPerlinNoise3D(float Time, float NoiseFrequency)
{
	FVector NoiseValue;

	NoiseValue.X = FMath::PerlinNoise1D(Time * NoiseFrequency);
	NoiseValue.Y = FMath::PerlinNoise1D((Time + 11.0f) * NoiseFrequency);
	NoiseValue.Z = FMath::PerlinNoise1D((Time + 37.0f) * NoiseFrequency);

	return NoiseValue;
}

