// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void ASnakeGameMode::BeginPlay()
{
	Super::BeginPlay();

	RandomCreate.GenerateNewSeed();
}

void ASnakeGameMode::Tick(float deltatime)
{
	Super::Tick(deltatime);

	if (mApplePtr == nullptr)
	{
		CreateApple();
	}
	
	if (mIsGameEnd == true) {
		UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, true);
	}
}

void ASnakeGameMode::CreateLineWall(int y, int z, FVector tileSize, TSubclassOf<AActor> wallActor)
{
	mTileCount.Y = y;
	mTileCount.Z = z;
	mTileSize = tileSize;

	/*for (int i = 0; i < mTileCount.Y; i++)
	{
		for (int j = 0; j < mTileCount.X; j++)
		{
			mActorAll[i][j] = nullptr;
		}
	}*/
	mActorAll.SetNumZeroed(mTileCount.Z);
	// Num() => size()
	for (size_t z = 0; z < mActorAll.Num(); z++)
	{
		mActorAll[z].SetNum(mTileCount.Y);
	}


	for (int i = 0; i < mTileCount.Y; i++)
	{
		FTransform trans;

		trans.SetLocation({0, mTileSize.Y * static_cast<float>(i), 0.0f});
		AActor* SpawnActor1 = GetWorld()->SpawnActor<AActor>(wallActor, trans);
		
		mActorAll[0][i] = SpawnActor1;
		
		trans.SetLocation({ 0, mTileSize.Y * static_cast<float>(i), mTileSize.Z * static_cast<float>(mTileCount.Z-1) });
		AActor* SpawnActor2 = GetWorld()->SpawnActor<AActor>(wallActor, trans);
		mActorAll[mTileCount.Z - 1][i] = SpawnActor2;

		mWallActArr.Add(SpawnActor1);
		mWallActArr.Add(SpawnActor2);
	}

	for (int i = 0; i < mTileCount.Z; i++)
	{
		FTransform trans;
		trans.SetLocation({ 0, 0, mTileSize.Z * i });
		AActor* SpawnActor1 = GetWorld()->SpawnActor<AActor>(wallActor, trans);
		mActorAll[i][0] = SpawnActor1;

		trans.SetLocation({ 0, mTileSize.Z * static_cast<float>(mTileCount.Y - 1), mTileSize.Z * i });
		AActor* SpawnActor2 = GetWorld()->SpawnActor<AActor>(wallActor, trans);
		mActorAll[i][mTileCount.Y - 1] = SpawnActor2;

		mWallActArr.Add(SpawnActor1);
		mWallActArr.Add(SpawnActor2);
	}

	//CreateApple();
}

bool ASnakeGameMode::IsSamePostion(FVector headPosVec)
{
	headPosVec.Y;
	headPosVec.Z;

	FVector appleLoc;
	appleLoc.Y = mApplePtr->GetActorLocation().Y;
	appleLoc.Z = mApplePtr->GetActorLocation().Z;

	//mApple.
	if (headPosVec.Y == appleLoc.Y && headPosVec.Z == appleLoc.Z)
	{
		mApplePtr->Destroy();
		mApplePtr = nullptr;
		//mApple = nullptr;
		bAppleFlag = true;


		return true;
	}
	else{
		for (int i = 0; i < mWallActArr.Num(); i++)
		{
			if (headPosVec.Z == mWallActArr[i]->GetActorLocation().Z &&
				headPosVec.Y == mWallActArr[i]->GetActorLocation().Y)
			{
				return true;
			}
		}
		FIntVector intVec = { 0, int(headPosVec.Y / 100.0f), int(headPosVec.Z / 100.0f) };

		if (intVec.Y<0 || intVec.Z<0 || intVec.Y >mTileCount.Y || intVec.Z > mTileCount.Z)
		{
			UE_LOG(LogTemp, Error, TEXT("intVec arraycount is worng"));
			return false;
		}
		if (mActorAll[intVec.Z][intVec.Y] != nullptr) {
			if (mActorAll[intVec.Z][intVec.Y]->ActorHasTag("Body")) {
				mIsGameEnd = true;
				return true;
			}
		}
		
	}
	
	return false;
}

void ASnakeGameMode::CreateApple()
{
	if (mApplePtr != nullptr)
	{	
		//UE_LOG(LogTemp, Error, TEXT("mApple == nullptr"));
		return;
	}
	else {

		if (bAppleFlag)
		{
			bAppleFlag = false;
			//int RandomIndex = RandomCreate.RandRange(0, EmptyPoint.Num() - 1);

			TArray<FIntVector> emptyArr;

			for (int z = 0; z < mActorAll.Num(); z++)
			{
				for (int y = 0; y < mActorAll[z].Num(); y++)
				{
					if (mActorAll[z][y] == nullptr)
						emptyArr.Add({ 0 , y, z });
				}
			}

			if (emptyArr.Num() == 0) {
				mIsGameEnd = true;
				return;
			}
			int tmp_rand = RandomCreate.RandRange(0, emptyArr.Num() - 1);

			FTransform Trans;
			
			

			Trans.SetLocation({ 0.0f, emptyArr[tmp_rand].Y * mTileSize.Y, emptyArr[tmp_rand].Z * mTileSize.Z });

			FVector tmp = mApple.GetDefaultObject()->GetActorLocation();// tActorLocation();
			
			mApplePtr = GetWorld()->SpawnActor<AActor>(mApple, Trans);
						
			//mApple.GetDefaultObject()->GetActorLocation().Y/GetTileSize
			SetActorArr(mApplePtr, emptyArr[tmp_rand].Y, emptyArr[tmp_rand].Z);
		}
	}
}

void ASnakeGameMode::RespawnApple()
{
	//if(mApplePtr != nullptr)

	CreateApple();
}

void ASnakeGameMode::SetActorArr(AActor* actor, int y, int z)
{
	if (actor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("actor == nullptr"));
		
	}
	if (y < 0 || y > mTileCount.Y || z < 0 || z > mTileCount.Z )
	{
		UE_LOG(LogTemp, Error, TEXT("actor index y, z  is worng"));
		return;
	}
	mActorAll[z][y] = actor;
}
