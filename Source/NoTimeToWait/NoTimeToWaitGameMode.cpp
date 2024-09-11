// Copyright Epic Games, Inc. All Rights Reserved.

#include "NoTimeToWaitGameMode.h"
#include "NoTimeToWaitCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "NTTWGameplayTags.h"

ANoTimeToWaitGameMode::ANoTimeToWaitGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ANoTimeToWaitGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	Difficulty Easy;
	Easy.CustomerNumber = 4;
	Easy.TotalTime = 120;
	Easy.OneStarMoney = 100;
	Easy.TwoStarMoney = 140;
	Easy.ThreeStarMoney = 200;
	DifficultyRules.Add(Easy);

	CustomerType Normal;
	Normal.Type = NTTWGameplayTags::TAG_Customer_Normal;
	Normal.MenuTime = 10.f;
	Normal.ServingTime = 10.f;
	Normal.EatingTime = 10.f;
	Normal.Money = 20;
	CustomerTypes.Add(Normal.Type, Normal);
}

void ANoTimeToWaitGameMode::StartPlay()
{
	Super::StartPlay();

	SetDifficulty(0);

	RemainingMinutes = CurrentDifficulty.TotalTime / 60;
	RemainingSeconds = CurrentDifficulty.TotalTime % 60;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ANoTimeToWaitGameMode::CountDown, 1.0f, true, 0.f);

}

void ANoTimeToWaitGameMode::EndLevel()
{
	// stop player input
	// display endlevel widget
}

Difficulty ANoTimeToWaitGameMode::GetDifficulty() const
{
	return CurrentDifficulty;
}

void ANoTimeToWaitGameMode::SetDifficulty(const int Index)
{
	if (DifficultyRules.Num() > Index)
	{
		CurrentDifficulty =  DifficultyRules[Index];
	}
}

CustomerType ANoTimeToWaitGameMode::GetCustomerType(const FGameplayTag& Type) const
{
	return CustomerTypes[Type];
}

void ANoTimeToWaitGameMode::UpdatePlayerMoney(const float Money)
{
	PlayerMoney += Money;
}

float ANoTimeToWaitGameMode::GetPlayerMoney() const
{
	return PlayerMoney;
}

void ANoTimeToWaitGameMode::CountDown()
{
	if (RemainingSeconds > 0)
	{
		RemainingSeconds--;
	}
	else if (RemainingMinutes > 0)
	{
		RemainingMinutes--;
		RemainingSeconds = 59;
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		EndLevel();
	}
}