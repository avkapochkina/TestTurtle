// Fill out your copyright notice in the Description page of Project Settings.


#include "Turtle.h"

#include "Kismet/GameplayStatics.h"

ATurtle::ATurtle()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
}

void ATurtle::BeginPlay()
{
	Super::BeginPlay();
}

void ATurtle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATurtle::Init(const FVector Spawn, const FVector End)
{
	SpawnPoint = Spawn;
	EndPoint = End;
	
	MovementDirection = EndPoint - SpawnPoint;
	MovementDirection.Normalize();
	
	if (AudioComponent)
	{
		AudioComponent = UGameplayStatics::SpawnSound2D(this, StartSound);
	}
	
	if (Particle)
	{
		UGameplayStatics::SpawnEmitterAttached(Particle, MeshComponent);
	}
}

void ATurtle::Movement()
{
	// Проверяем оставшееся до EndPoint расстояние
	// Если оно больше одного шага - продолжаем движение, меньше - отключаем звук движения и Tick
	
	const FVector Delta = EndPoint - GetActorLocation(); 
	if(Delta.Size() > Speed)
	{
		SetActorLocation(GetActorLocation() + Speed * MovementDirection);
		if (AudioComponent && !AudioComponent->IsActive())
		{
			AudioComponent = UGameplayStatics::SpawnSound2D(this, MovementSound);
		}
	}
	else
	{
		if (AudioComponent)
			AudioComponent->Stop();
		StopMovement();
	}
}

void ATurtle::StopMovement()
{
	SetActorTickEnabled(false);
	if (AudioComponent)
	{
		AudioComponent = UGameplayStatics::SpawnSound2D(this, StartSound);
	}
	
	if (Particle)
	{
		UGameplayStatics::SpawnEmitterAttached(Particle, MeshComponent);
	}
	
	UE_LOG(LogActor, Error, TEXT("ATurtle::StopMovement()"));
}

