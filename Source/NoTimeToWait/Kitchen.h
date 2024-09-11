// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "Kitchen.generated.h"

class AFood;

UCLASS()
class NOTIMETOWAIT_API AKitchen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKitchen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnCustomerOrder(const FGameplayTag& FoodType);

private:
	void InitializeFoodClassMap();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> CounterMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Food", meta = (AllowPrivateAccess = "true"))
	TMap<FGameplayTag, TSubclassOf<AFood>> FoodClassMap;
};
