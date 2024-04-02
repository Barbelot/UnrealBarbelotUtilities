
#include "BrownianMotion/BABrownianMotionComponent.h"

// Sets default values for this component's properties
UBABrownianMotionComponent::UBABrownianMotionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Default values


	bEnablePosition = true;
	PositionAxisScale = FVector::OneVector;
	PositionAmplitude = 100;
	PositionFrequency = 0.5f;
	PositionOffset = FVector::ZeroVector;
	bRandomizePositionTimeOffset = true;
	PositionTimeOffset = 0;

	bAlignWithMovement = false;

	bEnableRotation = false;
	RotationFrequency = .5f;
	RotationAmplitude = 360.0f;
	RotationAxisScale = FVector::OneVector;
	RotationOffset = FVector::ZeroVector;
	bRandomizeRotationTimeOffset = true;
	RotationTimeOffset = 0;

	PositionTime = 0;
	RotationTime = 0;
}


// Called when the game starts
void UBABrownianMotionComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get Starting transform
	StartingPosition = GetOwner()->GetRootComponent()->GetRelativeLocation();
	StartingRotation = GetOwner()->GetRootComponent()->GetRelativeRotation();

	if (bRandomizePositionTimeOffset)
	{
		PositionTimeOffset += FMath::RandRange(-10000, 0);
	}

	if (bRandomizeRotationTimeOffset)
	{
		RotationTimeOffset += FMath::RandRange(-10000, 0);
	}

	PositionTime = PositionTimeOffset;
	RotationTime = RotationTimeOffset;
}

// Called every frame
void UBABrownianMotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PreviousPosition = GetOwner()->GetActorLocation();

	// Apply position motion
	if (bEnablePosition) {
		PositionTime += DeltaTime * PositionFrequency;
		FVector NewLocation = GetPerlinNoise3D(PositionTime);
		NewLocation *= PositionAxisScale * PositionAmplitude;
		NewLocation += StartingPosition + PositionOffset;
		GetOwner()->SetActorRelativeLocation(NewLocation);
	}

	//Align with direction
	if (bAlignWithMovement) {

		FVector CurrentPosition = GetOwner()->GetActorLocation();

		if (CurrentPosition != PreviousPosition) {
			FVector CurrentDirection = CurrentPosition - PreviousPosition;
			CurrentRotation = CurrentDirection.Rotation();

			if (!bEnableRotation) {
				GetOwner()->SetActorRotation(CurrentRotation);
			}
		}
	}

	//Apply rotation motion
	if (bEnableRotation) {
		RotationTime += DeltaTime * RotationFrequency;
		FVector NewRotation = GetPerlinNoise3D(RotationTime);
		NewRotation *= RotationAxisScale * RotationAmplitude;
		NewRotation += RotationOffset;
		if (bAlignWithMovement) {
			GetOwner()->SetActorRotation(CurrentRotation + FRotator::MakeFromEuler(NewRotation));
		}
		else {
			GetOwner()->SetActorRelativeRotation(StartingRotation + FRotator::MakeFromEuler(NewRotation));
		}
	}
}

// Get 3D perlin noise vector
FVector UBABrownianMotionComponent::GetPerlinNoise3D(float Time)
{
	FVector NoiseValue;

	NoiseValue.X = FMath::PerlinNoise1D(Time);
	NoiseValue.Y = FMath::PerlinNoise1D((Time + 11.0f));
	NoiseValue.Z = FMath::PerlinNoise1D((Time + 37.0f));

	return NoiseValue;
}

