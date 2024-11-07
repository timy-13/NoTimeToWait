// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"

#include "RatAIController.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
    NodeName = "Find Random Location";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (ARatAIController* const Controller = Cast<ARatAIController>(OwnerComp.GetAIOwner()))
    {
        if (auto* const NPC = Controller->GetPawn())
        {
            auto const Origin = NPC->GetActorLocation();

            // get navigation system and generate random location in the nav mesh boundary
            if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
            {
                FNavLocation Location;
                if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location))
                {
                    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Location.Location);
                }

                // finish with success
                FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
                return EBTNodeResult::Succeeded;
            }  
        }
    }

    return EBTNodeResult::Failed;
}