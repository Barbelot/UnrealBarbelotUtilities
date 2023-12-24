    
#include "BrownianMotion/BAPolarBrownianMotionComponent.h"

// Sets default values for this component's properties
UBAPolarBrownianMotionComponent::UBAPolarBrownianMotionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Default values
	bEnableMotion = true;
	Amplitude = 1;
	RadiusAmplitude = 100;
	bUseArcLength = false;
	ThetaAmplitude = 180;
	PhiAmplitude = 180;
	Frequency = 0.5f;
	TimeOffset = 0;
	bRandomizeTimeOffset = true;
	PositionOffset = FVector::ZeroVector;
	RadiusOffset = 0;
	ThetaOffset = 0;
	PhiOffset = 0;
}
  

// Called when the game starts
void UBAPolarBrownianMotionComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get Starting position
	StartingPosition = GetOwner()->GetRootComponent()->GetRelativeLocation();

	if(bRandomizeTimeOffset)
	{
		TimeOffset += FMath::RandRange(-10000, 0);
	}
}

// Called every frame
void UBAPolarBrownianMotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Apply Brownian Motion
	if (bEnableMotion) {
		FVector NewLocation = StartingPosition + PositionOffset;
		FVector Noise = GetPerlinNoise3D(GetWorld()->GetTimeSeconds() + TimeOffset, Frequency);

		float Radius = RadiusAmplitude * Amplitude * Noise.X + RadiusOffset;

		float ThetaDegrees = ThetaAmplitude;
		float PhiDegrees = PhiAmplitude;

		if(bUseArcLength)
		{
			ThetaDegrees = 180 * ThetaAmplitude / (2 * UE_PI * Radius);
			PhiDegrees = 180 * PhiAmplitude / (2 * UE_PI * Radius);
		}

		float Theta = FMath::DegreesToRadians(ThetaDegrees) * Amplitude * Noise.Y + FMath::DegreesToRadians(ThetaOffset);
		float Phi = FMath::DegreesToRadians(PhiDegrees) * Amplitude * Noise.Z + FMath::DegreesToRadians(PhiOffset);

		NewLocation.X += Radius * FMath::Sin(Theta) * FMath::Cos(Phi);
		NewLocation.Y += Radius * FMath::Sin(Theta) * FMath::Sin(Phi);
		NewLocation.Z += Radius * FMath::Cos(Theta);

		GetOwner()->SetActorRelativeLocation(NewLocation);
	}
}

// Get 3D perlin noise vector
FVector UBAPolarBrownianMotionComponent::GetPerlinNoise3D(float Time, float NoiseFrequency)
{
	FVector NoiseValue;

	NoiseValue.X = FMath::PerlinNoise1D(Time * NoiseFrequency);
	NoiseValue.Y = FMath::PerlinNoise1D((Time + 11.0f) * NoiseFrequency);
	NoiseValue.Z = FMath::PerlinNoise1D((Time + 37.0f) * NoiseFrequency);

	return NoiseValue;
}

