// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeActor.h"
#include "SnakeHead.generated.h"


enum class DIRECTION
{
	RIGHT,
	LEFT,
	UP,
	DOWN
};

UCLASS()
class UE5STUDY_API ASnakeHead : public ASnakeActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeHead();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void LeftMove(float fvalue);

	UFUNCTION(BlueprintCallable)
	void RightMove(float fvalue);

	UFUNCTION(BlueprintCallable)
	void UpMove(float fvalue);

	UFUNCTION(BlueprintCallable)
	void DownMove(float fvalue);

	UFUNCTION(BlueprintCallable)
	void ActionMoveUp();

	UFUNCTION(BlueprintCallable)
		void ActionMoveDown();

	UFUNCTION(BlueprintCallable)
		void ActionMoveRight();

	UFUNCTION(BlueprintCallable)
		void ActionMoveLeft();

	UFUNCTION(BlueprintCallable)
		void AddBody(ASnakeActor* bodyactor);

	UFUNCTION(BlueprintCallable)
		void MoveBody(bool isAdd, ASnakeActor* newBody, FVector movePos);


	FORCEINLINE	TArray<ASnakeActor*> GetBodyAct() {
		return mBodyActArr;
	}


private:

	DIRECTION mDirection;

	UPROPERTY(Category = "SnakeBodyAct", EditAnywhere, Meta = (wallActors))
		TArray<ASnakeActor*> mBodyActArr /*= { nullptr }*/;

	UPROPERTY(Category = "SnakeModeData", EditAnywhere, DisplayName = "mApple")
		TSubclassOf<ASnakeActor> mBody;
};
