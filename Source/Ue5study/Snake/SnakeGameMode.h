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
	virtual void Tick(float deltatime) override;

public:

	UFUNCTION(BlueprintCallable)
	void CreateLineWall(int y, int z, FVector tileSize, TSubclassOf<AActor> wallActor);

	FORCEINLINE FVector GetTileSize() {
		return mTileSize;
	}

	FORCEINLINE FIntVector3 GetTileCount() {
		return mTileCount;
	}

	UFUNCTION(BlueprintCallable)
		bool IsSamePostion(FVector headPosVec);

	UFUNCTION(BlueprintCallable)
		void CreateApple();

	UFUNCTION(BlueprintCallable)
		void RespawnApple();


	UFUNCTION(BlueprintCallable)
		void SetActorArr(AActor* actor, int y, int z);



	bool bAppleFlag = true;

private:
	FVector mTileSize;
	FIntVector3	mTileCount;

	FRandomStream RandomCreate = FRandomStream();

	//UProperty(blueprint)
	TArray<TArray<class AActor*>> mActorAll;

	UPROPERTY(Category = "SnakeModeData", EditAnywhere, Meta = (wallActors))
	TArray<AActor*> mWallActArr /*= { nullptr }*/;

	//UPROPERTY(Category = "SnakeModeData", EditAnywhere, Meta = (wallActors))
	//TArray<AActor*> mBodyActArr /*= { nullptr }*/;

	UPROPERTY(Category = "SnakeModeData", EditAnywhere, DisplayName = "mApple")
	TSubclassOf<AActor> mApple;


	

	AActor* mApplePtr;


};
