// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisPawn.h"
#include "Kismet/GameplayStatics.h"
#include "TetrisGameMode.h"
#include "TetrisActor.h"

// Sets default values
ATetrisPawn::ATetrisPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATetrisPawn::BeginPlay()
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
	ATetrisGameMode* TetrisGameMode = Cast<ATetrisGameMode>(GameModePtr);

	if (nullptr == TetrisGameMode && false == TetrisGameMode->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == SnakeGameMode && false == SnakeGameMode->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		return;
	}

	FIntVector3 Count = TetrisGameMode->getWallCount();
	FVector Size = TetrisGameMode->getBlockSize();
	// /°¡ »çÄ¢¿¬»êÁß °¡Àå ´À¸° ¿¬»êÀÔ´Ï´Ù.
	// /2 ÇÒ¹Ù¿¡´Â *0.5f


	mCenter = { -1000.0f, Size.Y * Count.Y * 0.5f, Size.Z * Count.Z * 0.5f };

	SetActorLocation(mCenter);
	mCenter = { 0.0f , Size.Y * Count.Y * 0.5f, Size.Z * Count.Z * 0.5f };

	SpawnTetrisBlock();
}

// Called every frame
void ATetrisPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATetrisPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ATetrisPawn::SpawnTetrisBlock()
{
	FTransform trans;
	trans.SetLocation(mCenter);
	GetWorld()->SpawnActor<ATetrisActor>(mControlBlock, trans);

	return false;
}

