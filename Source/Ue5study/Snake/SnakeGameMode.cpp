// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameMode.h"

void ASnakeGameMode::BeginPlay()
{
	Super::BeginPlay();

	
}

void ASnakeGameMode::CreateLineWall(int x, int y, FVector tileSize, TSubclassOf<AActor> wallActor)
{
	mTileCount.X = x;
	mTileCount.Y = y;
	mTileSize = tileSize;


	for (int i = 0; i < mTileCount.X + 2; i++)
	{
		FTransform trans;

		trans.SetLocation({0, mTileSize.X * static_cast<float>(i), 0.0f});
		AActor* SpawnActor1 = GetWorld()->SpawnActor<AActor>(wallActor, trans);
		
		trans.SetLocation({ 0, mTileSize.X * static_cast<float>(i), mTileSize.Y * static_cast<float>(mTileCount.Y + 1) });
		AActor* SpawnActor2 = GetWorld()->SpawnActor<AActor>(wallActor, trans);

	}

	for (int i = 0; i < mTileCount.Y + 2; i++)
	{
		FTransform trans;
		trans.SetLocation({ 0, 0, mTileSize.X * i });
		AActor* SpawnActor1 = GetWorld()->SpawnActor<AActor>(wallActor, trans);
		trans.SetLocation({ 0, mTileSize.X * static_cast<float>(mTileCount.X + 1), mTileSize.Y * i });
		AActor* SpawnedActor2 = GetWorld()->SpawnActor<AActor>(wallActor, trans);
	
	}
}
