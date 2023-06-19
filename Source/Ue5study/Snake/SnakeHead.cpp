// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeHead.h"

// Sets default values
ASnakeHead::ASnakeHead()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASnakeHead::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnakeHead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASnakeHead::LeftMove(float fvalue)
{
	if (fvalue == 0)
		return;

	AddActorLocalOffset(FVector::LeftVector);
}

void ASnakeHead::RightMove(float fvalue)
{
	if (fvalue == 0)
		return;
	AddActorLocalOffset(FVector::RightVector);
}

void ASnakeHead::UpMove(float fvalue)
{
	if (fvalue == 0)
		return;
	AddActorLocalOffset(FVector::UpVector);
}

void ASnakeHead::DownMove(float fvalue)
{
	if (fvalue == 0)
		return;
	AddActorLocalOffset(FVector::DownVector);
}

void ASnakeHead::ActionMoveUp()
{
	AddActorLocalOffset(FVector::UpVector * 100.0f);
}

void ASnakeHead::ActionMoveDown()
{
	AddActorLocalOffset(FVector::DownVector * 100.0f);
}

void ASnakeHead::ActionMoveRight()
{
	AddActorLocalOffset(FVector::RightVector * 100.0f);
}

void ASnakeHead::ActionMoveLeft()
{
	AddActorLocalOffset(FVector::LeftVector * 100.0f);
}

