// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetTableLocation.h"

#include "NavigationSystem.h"
#include "CustomerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GetTableLocation::UBTTask_GetTableLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Get Table Location in NavMesh";
}


EBTNodeResult::Type UBTTask_GetTableLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get AIController
	if (auto* const Controller = Cast<ACustomerAIController>(OwnerComp.GetAIOwner()))
	{
		// get Customer
		if (auto* const Customer = Controller->GetPawn())
		{
			// get customer location to use as origin
			auto const Origin = Customer->GetActorLocation();

			// get TableLocation

			// want to have all tables stored in a dictionary?
			// find a table with the nocustomer value
			FVector TableLocation = FVector(0, 0, 0);


			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), TableLocation);
			
			// finish with success
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}