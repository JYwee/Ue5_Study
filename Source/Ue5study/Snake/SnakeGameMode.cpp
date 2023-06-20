// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameMode.h"

void ASnakeGameMode::BeginPlay()
{
	Super::BeginPlay();

	
}

void ASnakeGameMode::CreateLineWall(int y, int z, FVector tileSize, TSubclassOf<AActor> wallActor)
{
	mTileCount.Y = y;
	mTileCount.Z = z;
	mTileSize = tileSize;


	for (int i = 0; i < mTileCount.Y + 2; i++)
	{
		FTransform trans;

		trans.SetLocation({0, mTileSize.Y * static_cast<float>(i), 0.0f});
		AActor* SpawnActor1 = GetWorld()->SpawnActor<AActor>(wallActor, trans);
		
		trans.SetLocation({ 0, mTileSize.Y * static_cast<float>(i), mTileSize.Z * static_cast<float>(mTileCount.Z + 1) });
		AActor* SpawnActor2 = GetWorld()->SpawnActor<AActor>(wallActor, trans);

	}

	for (int i = 0; i < mTileCount.Z + 2; i++)
	{
		FTransform trans;
		trans.SetLocation({ 0, 0, mTileSize.Y * i });
		AActor* SpawnActor1 = GetWorld()->SpawnActor<AActor>(wallActor, trans);
		trans.SetLocation({ 0, mTileSize.Y * static_cast<float>(mTileCount.Y + 1), mTileSize.Z * i });
		AActor* SpawnedActor2 = GetWorld()->SpawnActor<AActor>(wallActor, trans);
	
	}
}
