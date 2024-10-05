// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayTagContainer.h"
#include "NoTimeToWaitGameMode.generated.h"

USTRUCT(BlueprintType)
struct FDifficulty
{
	GENERATED_BODY()

	int CustomerNumber;
	int TotalTime;

	UPROPERTY(BlueprintReadWrite, Category = "Game")
	float OneStarMoney;

	UPROPERTY(BlueprintReadWrite, Category = "Game")
	float TwoStarMoney;

	UPROPERTY(BlueprintReadWrite, Category = "Game")
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
class ANoTimeToWaitPlayerController;

UCLASS(minimalapi)
class ANoTimeToWaitGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANoTimeToWaitGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void BeginPlay() override;
	virtual void StartPlay() override;
	void EndLevel();

	FDifficulty GetDifficulty() const;
	void SetDifficulty(const int Index);

	CustomerType GetCustomerType(const FGameplayTag& Type) const;

	float GetPlayerMoney() const;
	void UpdatePlayerMoney(const float Money);


protected:
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void EndGame();

private:
	void HandleGameStart();

	void CountDown();

	void CalculateFinalScore();

	ANoTimeToWaitPlayerController* PlayerController;

	TArray<FDifficulty> DifficultyRules;

	TMap<FGameplayTag, CustomerType> CustomerTypes;

	UPROPERTY(BlueprintReadOnly, Category = "Game", meta = (AllowPrivateAccess = "true"))
	FDifficulty CurrentDifficulty;

	FTimerHandle TimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Game");
	float StartDelay;

	UPROPERTY(BlueprintReadOnly, Category = "Game", meta = (AllowPrivateAccess = "true"))
	int RemainingMinutes;

	UPROPERTY(BlueprintReadOnly, Category = "Game", meta = (AllowPrivateAccess = "true"))
	int RemainingSeconds;

	UPROPERTY(BlueprintReadOnly, Category = "Game", meta = (AllowPrivateAccess = "true"))
	int PlayerMoney;

	UPROPERTY(BlueprintReadOnly, Category = "Game", meta = (AllowPrivateAccess = "true"))
	FString FinalScore;
};



