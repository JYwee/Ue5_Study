// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePawn.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeGameMode.h"


// Sets default values
ASnakePawn::ASnakePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASnakePawn::BeginPlay()
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
	

	FVector Center = { -1000.0f, Size.Y * Count.Y * 0.5f, Size.Z * Count.Z * 0.5f };

	SetActorLocation(Center);
}

// Called every frame
void ASnakePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASnakePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

