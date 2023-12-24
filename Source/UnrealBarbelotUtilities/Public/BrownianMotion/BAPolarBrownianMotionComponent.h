
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BAPolarBrownianMotionComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALBARBELOTUTILITIES_API UBAPolarBrownianMotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBAPolarBrownianMotionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	FVector StartingPosition;

	FVector GetPerlinNoise3D(float Time, float Scale);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion")
	bool bEnableMotion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion")
	float Frequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Amplitude")
	float Amplitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Amplitude")
	float RadiusAmplitude;

	/* Set the theta and phi amplitudes in centimeters instead of degrees. Useful to get a smoother velocity at a fixed radius. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Amplitude")
	bool bUseArcLength;

	/* Polar angle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Amplitude")
	float ThetaAmplitude;

	/* Azimuthal angle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Amplitude")
	float PhiAmplitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Offset")
	float TimeOffset;

	/* Add a random time offset at begin play */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Offset")
	bool bRandomizeTimeOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Offset")
	FVector PositionOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Offset")
	float RadiusOffset;

	/* Polar angle offset in degrees */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Offset")
	float ThetaOffset;

	/* Azimuthal angle offset in degrees */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Offset")
	float PhiOffset;


};
