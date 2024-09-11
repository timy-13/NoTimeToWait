// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTags.h"
#include "Navigation/PathFollowingComponent.h"
#include "NoTimeToWaitGameMode.h"
#include "Customer.generated.h"

class UTagHandlerComponent;
class UTimerHandlerComponent;
class UCustomerSpawnerComponent;
class ANoTimeToWaitGameMode;
class ATable;


DECLARE_DELEGATE(FOnCustomerSpawnedSignature);
DECLARE_DELEGATE(FOnCustomerFinishedSignature);

UCLASS()
class NOTIMETOWAIT_API ACustomer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomer();

	FOnCustomerSpawnedSignature OnCustomerSpawnedDelegate;
	FOnCustomerFinishedSignature OnCustomerFinishedDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FGameplayTag GetFoodType() const;
	void SetFoodType(const FGameplayTag& TypeTag);

	ATable* GetTable() const;
	void SetTable(ATable* CustomerTable);

	FVector GetTableLocation() const;

	FVector GetDespawnLocation() const;
	void SetDespawnLocation(const FVector& Location);

	FGameplayTag GetCustomerTypeTag() const;
	void SetCustomerType(const FGameplayTag& TypeTag);

	void OnReceivedMenu();
	void OnReceivedFood();
	void Leave();
	void Despawn();

	void OnMoveToDespawnFinished(FAIRequestID ID, const FPathFollowingResult& Result);

	FTimerHandle TimerHandle;

private:
	void CalculateMoney(const float RemainingTime);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTagHandlerComponent> TagHandler;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTimerHandlerComponent> TimerHandler;

	TObjectPtr<ANoTimeToWaitGameMode> GameMode;

	TObjectPtr<ATable> Table;

	UPROPERTY(VisibleAnywhere, Category = "Food")
	FGameplayTag FoodType;
	FGameplayTag CustomerTypeTag;
	CustomerType Type;

	FVector TableLocation;
	FVector DespawnLocation;

	float Money;
	float TotalRemainingTime;
};
