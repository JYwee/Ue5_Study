// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SnakeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UE5STUDY_API ASnakeGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void CreateLineWall(int x, int y, FVector tileSize, TSubclassOf<AActor> wallActor);

	FORCEINLINE FVector GetTileSize() {
		return mTileSize;
	}

	FORCEINLINE FIntVector2 GetTileCount() {
		return mTileCount;
	}

private:
	FVector mTileSize;
	FIntVector2	mTileCount;
};
