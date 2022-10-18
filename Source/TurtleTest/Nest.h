// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Nest.generated.h"

UCLASS()
class TURTLETEST_API ANest : public AActor
{
	GENERATED_BODY()

public:
	ANest();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshComponent;
	
	// Конечная точка маршрута черепашки
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EndPoint;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SpawnBP;
	
	// Массив черепашек
	// Одновременно в каждом гнезде существует не более TurtlesMax черепашек
	UPROPERTY()
	TArray<AActor*> Turtles;
	int TurtlesMax = 10;
	
	UFUNCTION(BlueprintCallable)
	void Spawn();
};
