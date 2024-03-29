
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
	FVector AxisAmplitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Offset")
	float TimeOffset;

	/* Add a random time offset at begin play */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Offset")
	bool bRandomizeTimeOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Brownian Motion|Offset")
	FVector PositionOffset;
};
