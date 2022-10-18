// Fill out your copyright notice in the Description page of Project Settings.


#include "Nest.h"
#include "Turtle.h"

ANest::ANest()
{
	PrimaryActorTick.bCanEverTick = false;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
}

void ANest::BeginPlay()
{
	Super::BeginPlay();	
}

void ANest::Spawn()
{
	if(GetWorld() && SpawnBP)
	{
		if(Turtles.Num() > TurtlesMax)
		{
			Turtles[0]->Destroy();
			for(int i = 0; i < Turtles.Num() - 1; i++)
				Turtles[i] = Turtles[i + 1];
		}
		
		FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
		SpawnParameters.Owner = this->GetOwner();
		ATurtle* Turtle = GetWorld()->SpawnActor<ATurtle>(SpawnBP, GetActorLocation(), GetActorRotation(), SpawnParameters);
		UE_LOG(LogActor, Warning, TEXT("Spawn completed"));
		Turtle->Init(GetActorLocation(), EndPoint);
		Turtles.Add(Turtle);
	}
}
