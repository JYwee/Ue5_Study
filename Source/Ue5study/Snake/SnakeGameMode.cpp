// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameMode.h"

void ASnakeGameMode::BeginPlay()
{
	Super::BeginPlay();

	
}

void ASnakeGameMode::CreateLineWall(int x, int y, TSubclassOf<AActor> wallActor)
{
	for (int i = 0; i < x+2; i++)
	{
		FTransform trans;
		
		AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(wallActor, trans);
	}
}
