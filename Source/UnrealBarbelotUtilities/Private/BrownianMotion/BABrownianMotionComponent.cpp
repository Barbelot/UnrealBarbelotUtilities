
#include "BrownianMotion/BABrownianMotionComponent.h"

// Sets default values for this component's properties
UBABrownianMotionComponent::UBABrownianMotionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Default values
	bEnableMotion = true;
	Scale = FVector::OneVector;
	Amplitude = 100;
	Frequency = 0.5f;
	TimeOffset = 0;
	PositionOffset = FVector::ZeroVector;
}


// Called when the game starts
void UBABrownianMotionComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get Starting position
	StartingPosition = GetOwner()->GetRootComponent()->GetRelativeLocation();
}

// Called every frame
void UBABrownianMotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Apply Brownian Motion
	if (bEnableMotion) {
		FVector NewLocation = GetPerlinNoise3D(GetWorld()->GetTimeSeconds() + TimeOffset, Frequency);
		NewLocation *= Scale * Amplitude;
		NewLocation += StartingPosition + PositionOffset;
		GetOwner()->SetActorRelativeLocation(NewLocation);
	}
}

// Get 3D perlin noise vector
FVector UBABrownianMotionComponent::GetPerlinNoise3D(float Time, float NoiseFrequency)
{
	FVector NoiseValue;

	NoiseValue.X = FMath::PerlinNoise1D(Time * NoiseFrequency);
	NoiseValue.Y = FMath::PerlinNoise1D((Time + 10.0f) * NoiseFrequency);
	NoiseValue.Z = FMath::PerlinNoise1D((Time + 30.0f) * NoiseFrequency);

	return NoiseValue;
}

