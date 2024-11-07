// Fill out your copyright notice in the Description page of Project Settings.


#include "RatAIController.h"

#include "Rat.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ARatAIController::ARatAIController(FObjectInitializer const& ObjectInitializer)
{
    SetupPerceptionSystem();
}

void ARatAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (ARat* const Rat = Cast<ARat>(InPawn))
    {
        if (UBehaviorTree* const Tree = Rat->GetBehaviorTree())
        {
            UBlackboardComponent* BlackboardComponent;
            UseBlackboard(Tree->BlackboardAsset, BlackboardComponent);
            Blackboard = BlackboardComponent;
            RunBehaviorTree(Tree);
        }
    }
}

void ARatAIController::SetupPerceptionSystem()
{
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
    if (SightConfig)
    {
        SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

        SightConfig->SightRadius = 500.f;
        SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
        SightConfig->PeripheralVisionAngleDegrees = 90.f;
        SightConfig->SetMaxAge(5.f);
        SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
        SightConfig->DetectionByAffiliation.bDetectEnemies = true;
        SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
        SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

        GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
        GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ARatAIController::OnTargetDetected);
        GetPerceptionComponent()->ConfigureSense(*SightConfig);
    }
}

void ARatAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{

}
