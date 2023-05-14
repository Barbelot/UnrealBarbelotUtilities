// Fill out your copyright notice in the Description page of Project Settings.

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Brownian Motion")
	bool bEnableMotion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brownian Motion")
	FVector Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brownian Motion")
	float Amplitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brownian Motion")
	float Frequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brownian Motion")
	float TimeOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brownian Motion")
	FVector PositionOffset;
};
