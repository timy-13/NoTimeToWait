// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "RatAIController.generated.h"


class UAISenseConfig_Sight;

/**
 * 
 */
UCLASS()
class NOTIMETOWAIT_API ARatAIController : public AAIController
{
	GENERATED_BODY()

public:
    explicit ARatAIController(FObjectInitializer const& ObjectInitializer);

protected:
    virtual void OnPossess(APawn* InPawn) override;

private:
    UAISenseConfig_Sight* SightConfig;

    void SetupPerceptionSystem();

    UFUNCTION()
    void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);
	
};
