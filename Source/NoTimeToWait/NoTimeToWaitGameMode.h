// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayTagContainer.h"
#include "NoTimeToWaitGameMode.generated.h"

struct Difficulty
{
	int CustomerNumber;
	int TotalTime;
	float OneStarMoney;
	float TwoStarMoney;
	float ThreeStarMoney;
};

struct CustomerType
{
	FGameplayTag Type;
	float MenuTime; // Max time to wait for menu
	float ServingTime; // Max time to be served
	float EatingTime;
	float Money;
};

class TableHandler;

UCLASS(minimalapi)
class ANoTimeToWaitGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANoTimeToWaitGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void StartPlay() override;
	void EndLevel();

	Difficulty GetDifficulty() const;
	void SetDifficulty(const int Index);

	CustomerType GetCustomerType(const FGameplayTag& Type) const;

	float GetPlayerMoney() const;
	void UpdatePlayerMoney(const float Money);


private:
	void CountDown();

	TArray<Difficulty> DifficultyRules; // initialize in InitGame
	// store difficulty rules

	TMap<FGameplayTag, CustomerType> CustomerTypes;

	Difficulty CurrentDifficulty;

	FTimerHandle TimerHandle;

	UPROPERTY(BlueprintReadOnly, Category = "Money", meta = (AllowPrivateAccess = "true"))
	float PlayerMoney;

	UPROPERTY(BlueprintReadOnly, Category = "Timer", meta = (AllowPrivateAccess = "true"))
	int RemainingMinutes;

	UPROPERTY(BlueprintReadOnly, Category = "Timer", meta = (AllowPrivateAccess = "true"))
	int RemainingSeconds;
};



