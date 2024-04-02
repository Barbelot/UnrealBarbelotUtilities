
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BABrownianMotionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALBARBELOTUTILITIES_API UBABrownianMotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBABrownianMotionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	FVector StartingPosition;
	FRotator StartingRotation;

	FVector PreviousPosition;

	FRotator CurrentRotation;

	float PositionTime;
	float RotationTime;

	FVector GetPerlinNoise3D(float Time);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* Enable brownian motion on actor relative position */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Position")
	bool bEnablePosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Position")
	float PositionFrequency;

	/* Movement amplitude in cm */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Position")
	float PositionAmplitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Position")
	FVector PositionAxisScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Position")
	FVector PositionOffset;

	/* Add a random time offset at begin play */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Position")
	bool bRandomizePositionTimeOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Position")
	float PositionTimeOffset;

	/* Align the actor forward axis with the movement direction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Rotation")
	bool bAlignWithMovement;

	/* Enable brownian motion on actor relative rotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Rotation")
	bool bEnableRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Rotation")
	float RotationFrequency;

	/* Rotation amplitude in degrees */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Rotation")
	float RotationAmplitude;

	/* Relative axis scale */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Rotation")
	FVector RotationAxisScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Rotation")
	FVector RotationOffset;

	/* Add a random time offset at begin play */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Rotation")
	bool bRandomizeRotationTimeOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Rotation")
	float RotationTimeOffset;
};
