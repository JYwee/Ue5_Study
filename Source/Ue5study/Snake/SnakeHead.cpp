// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeHead.h"
#include "SnakeGameMode.h"
#include "Kismet/GameplayStatics.h"

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
	
	AGameModeBase* GameModePtr = UGameplayStatics::GetGameMode(GetWorld());
	if (nullptr == GameModePtr)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == GameMode)"), __FUNCTION__, __LINE__);
		return;
	}
	if (false == GameModePtr->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == GameMode)"), __FUNCTION__, __LINE__);
		return;
	}

	// ´Ù¿îÄ³½ºÆÃ
	ASnakeGameMode* SnakeGameMode = Cast<ASnakeGameMode>(GameModePtr);

	if (nullptr == SnakeGameMode && false == SnakeGameMode->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == SnakeGameMode && false == SnakeGameMode->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		return;
	}

	FIntVector3 Count = SnakeGameMode->GetTileCount();
	FVector Size = SnakeGameMode->GetTileSize();
	// /°¡ »çÄ¢¿¬»êÁß °¡Àå ´À¸° ¿¬»êÀÔ´Ï´Ù.
	// /2 ÇÒ¹Ù¿¡´Â *0.5f

	FIntVector3 Center;
	Center.Y = Count.Y / 2;
	Center.Z = Count.Z / 2;

	FVector Center2 = { 0, Size.Y * Center.Y, Size.Z * Center.Z };

	SetActorLocation(Center2);

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

