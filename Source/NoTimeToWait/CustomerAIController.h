// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CustomerAIController.generated.h"

class ACustomer;

/**
 * 
 */
UCLASS()
class NOTIMETOWAIT_API ACustomerAIController : public AAIController
{
	GENERATED_BODY()
public:
	explicit ACustomerAIController(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	void SetTableLocation();
	void SetDespawnLocation();

	void OnMoveToTableFinished(FAIRequestID ID, const FPathFollowingResult& Result);

	ACustomer* Customer;
};
