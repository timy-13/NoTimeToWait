// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CustomerSpawnerComponent.generated.h"

class ACustomer;
class ATable;
class UTableManagerSubsystem;
struct FGameplayTag;
struct FDifficulty;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NOTIMETOWAIT_API UCustomerSpawnerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCustomerSpawnerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SpawnCustomers(const FDifficulty& DifficultyLevel);

private:
	void SpawnCustomer(ATable* Table, const FGameplayTag& FoodType);

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<ACustomer> CustomerClass;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<ATable> TableClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn", meta = (AllowPrivateAccess = "true"))
	UTableManagerSubsystem* TableManager;
};
