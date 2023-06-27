// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TetrisGameMode.generated.h"


/**
 * 
 */
UCLASS()
class UE5STUDY_API ATetrisGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	
	virtual void BeginPlay() override;

	virtual void Tick(float deltaTime) override;

	UFUNCTION(BlueprintCallable)
		void InitWallSize(int y, int z, FVector blockSize, TSubclassOf<AActor> wallActor);

	FORCEINLINE FIntVector getWallCount() {
		return mWallCount;
	}
	FORCEINLINE FVector getBlockSize() {
		return mBlockSize;
	}



private :

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> mWallActor;

	FIntVector mWallCount;

	FVector mBlockSize;


	//ATetrisActor* mTerisActor;
	//TArray<TArray<class ATetrisActor*>> mLineActor;

	
	TArray<AActor*> mWallActArr;

	TArray<TArray<class AActor*>> mAllTetrisAct;

	
	
};
