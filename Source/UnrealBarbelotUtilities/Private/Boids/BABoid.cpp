// Fill out your copyright notice in the Description page of Project Settings.


#include "Boids/BABoid.h"

// Sets default values
ABABoid::ABABoid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABABoid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABABoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

