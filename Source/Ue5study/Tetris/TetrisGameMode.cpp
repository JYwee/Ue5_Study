// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisGameMode.h"
#include "TetrisActor.h"

void ATetrisGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ATetrisGameMode::Tick(float deltaTime)
{
	Super::Tick(deltaTime);


}

void ATetrisGameMode::InitWallSize(int y, int z, FVector blockSize, TSubclassOf<AActor> wallActor)
{
	mWallCount.Y = y;
	mWallCount.Z = z;

	mBlockSize.Y = blockSize.Y;
	mBlockSize.Z = blockSize.Z;

	

	mAllTetrisAct.SetNumZeroed(mWallCount.Z);
	// Num() => size()
	for (int z = 0; z < mAllTetrisAct.Num(); z++)
	{
		mAllTetrisAct[z].SetNum(mWallCount.Y);
	}


	for (int i = 0; i < mWallCount.Y; i++)
	{
		FTransform trans;

		trans.SetLocation({ 0, mBlockSize.Y * static_cast<float>(i), 0.0f });
		AActor* SpawnActor1 = GetWorld()->SpawnActor<AActor>(wallActor, trans);

		mAllTetrisAct[0][i] = SpawnActor1;

		trans.SetLocation({ 0, mBlockSize.Y * static_cast<float>(i), mBlockSize.Z * static_cast<float>(mWallCount.Z - 1) });
		AActor* SpawnActor2 = GetWorld()->SpawnActor<AActor>(wallActor, trans);
		mAllTetrisAct[mWallCount.Z - 1][i] = SpawnActor2;

		mWallActArr.Add(SpawnActor1);
		mWallActArr.Add(SpawnActor2);
	}

	for (int i = 0; i < mWallCount.Z; i++)
	{
		FTransform trans;
		trans.SetLocation({ 0, 0, mBlockSize.Z * i });
		AActor* SpawnActor1 = GetWorld()->SpawnActor<AActor>(wallActor, trans);
		mAllTetrisAct[i][0] = SpawnActor1;

		trans.SetLocation({ 0, mBlockSize.Z * static_cast<float>(mWallCount.Y - 1), mBlockSize.Z * i });
		AActor* SpawnActor2 = GetWorld()->SpawnActor<AActor>(wallActor, trans);
		mAllTetrisAct[i][mWallCount.Y - 1] = SpawnActor2;

		mWallActArr.Add(SpawnActor1);
		mWallActArr.Add(SpawnActor2);
	}


}
