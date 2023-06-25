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

	GetSnakeGameMode()->SetActorArr(this, Center.Y, Center.Z);

	FVector Center2 = { 0, Size.Y * Center.Y, Size.Z * Center.Z };

	SetActorLocation(Center2);

	//mBodyActArr.Add(this);

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
	FVector movePos = FVector::UpVector * 100.0f;
	bool isAddNewbody = false;
	ASnakeActor* newBody = nullptr;
	ASnakeGameMode* SnGameMode = GetSnakeGameMode();
	if (SnGameMode->IsSamePostion(GetActorLocation() + movePos)) {
		if (false == SnGameMode->bAppleFlag)
		{
			return;
		}
		else
		{
			isAddNewbody = true;
			SnGameMode->RespawnApple();
		}
	}
	
	MoveBody(isAddNewbody, newBody, movePos);

}

void ASnakeHead::ActionMoveDown()
{
	ASnakeGameMode* SnGameMode = GetSnakeGameMode();
	bool isAddNewbody = false;
	ASnakeActor* newBody = nullptr;
	FVector movePos = FVector::DownVector * 100.0f;
	if (SnGameMode->IsSamePostion(GetActorLocation() + movePos)) {
		if (false == SnGameMode->bAppleFlag)
		{
			return;
		}
		else
		{
			isAddNewbody = true;
			SnGameMode->RespawnApple();
		}
	}
	MoveBody(isAddNewbody, newBody, movePos);
}

void ASnakeHead::ActionMoveRight()
{
	ASnakeGameMode* SnGameMode = GetSnakeGameMode();
	bool isAddNewbody = false;
	ASnakeActor* newBody = nullptr;
	FVector movePos = FVector::RightVector * 100.0f;

	if (SnGameMode->IsSamePostion(GetActorLocation() + movePos)) {
		if (false == SnGameMode->bAppleFlag)
		{
			return;
		}
		else
		{
			isAddNewbody = true;
			SnGameMode->RespawnApple();
		}
	}
	MoveBody(isAddNewbody, newBody, movePos);
}

void ASnakeHead::ActionMoveLeft()
{
	ASnakeGameMode* SnGameMode = GetSnakeGameMode();
	bool isAddNewbody = false;
	ASnakeActor* newBody = nullptr;
	FVector movePos = FVector::LeftVector * 100.0f;
	if (SnGameMode->IsSamePostion(GetActorLocation() + movePos)) {
		if (false == SnGameMode->bAppleFlag)
		{
			return;
		}
		else
		{
			isAddNewbody = true;
			SnGameMode->RespawnApple();
		}
	}
	MoveBody(isAddNewbody, newBody, movePos);
}

void ASnakeHead::AddBody(ASnakeActor* bodyactor)
{
	mBodyActArr.Add(bodyactor);
}

void ASnakeHead::MoveBody(bool isAdd, ASnakeActor* newBody, FVector movePos)
{
	ASnakeGameMode* SnGameMode = GetSnakeGameMode();
	int bodycount = mBodyActArr.Num();

	if (bodycount == 0)
	{
		if (isAdd) {
			FTransform trans;
			trans.SetLocation({ 0, GetActorLocation().Y,  GetActorLocation().Z });
			newBody = GetWorld()->SpawnActor<ASnakeActor>(mBody, trans);
			mBodyActArr.Add(newBody);
			SnGameMode->SetActorArr(newBody, GetActorLocation().Y / SnGameMode->GetTileSize().Y, GetActorLocation().Z / SnGameMode->GetTileSize().Z);

		}
		else {
			SnGameMode->SetActorArr(newBody, GetActorLocation().Y / SnGameMode->GetTileSize().Y, GetActorLocation().Z / SnGameMode->GetTileSize().Z);
		}
		AddActorLocalOffset(movePos);
		SnGameMode->SetActorArr(this, GetActorLocation().Y / 100.0f, GetActorLocation().Z / 100.0f);
	}
	else
	{
		FVector prev = GetActorLocation();
		AddActorLocalOffset(movePos);
		//SnGameMode->SetActorArr(this, GetActorLocation().Y / 100.0f, GetActorLocation().Z / 100.0f);

		for (int i = 0; i < bodycount; i++)
		{
			FVector tmp = prev;
			prev = mBodyActArr[i]->GetActorLocation();
			mBodyActArr[i]->SetActorLocation(tmp);
			
			if (i == bodycount - 1)
			{
				if (isAdd)
				{
					FTransform trans;
					trans.SetLocation({ 0, prev.Y,  prev.Z });
					newBody = GetWorld()->SpawnActor<ASnakeActor>(mBody, trans);
					mBodyActArr.Add(newBody);
				}
				SnGameMode->SetActorArr(newBody, prev.Y / 100.0f, prev.Z / 100.0f);
			}
			else
			{
				SnGameMode->SetActorArr(mBodyActArr[i], mBodyActArr[i]->GetActorLocation().Y / SnGameMode->GetTileSize().Y, mBodyActArr[i]->GetActorLocation().Z / SnGameMode->GetTileSize().Z);
			}

			
			//SnGameMode->SetActorArr(mBodyActArr[i], mBodyActArr[i]->GetActorLocation().Y / 100.0f, mBodyActArr[i]->GetActorLocation().Z / 100.0f);
		}
	}
}
	

