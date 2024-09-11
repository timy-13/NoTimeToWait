// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerAIController.h"

#include "Customer.h"
#include "CustomerSpawnerComponent.h"
#include "NoTimeToWaitGameMode.h"
#include "Table.h"
#include "TagHandlerComponent.h"
#include "NTTWGameplayTags.h"

#include "Navigation/PathFollowingComponent.h"
#include "Kismet/GameplayStatics.h"

ACustomerAIController::ACustomerAIController(FObjectInitializer const& ObjectInitializer)
{

}

void ACustomerAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("Possessed"));
	if (ACustomer* InCustomer = Cast<ACustomer>(InPawn))
	{
		Customer = InCustomer;

		Customer->OnCustomerSpawnedDelegate.BindUObject(this, &ACustomerAIController::SetTableLocation);
		Customer->OnCustomerFinishedDelegate.BindUObject(this, &ACustomerAIController::SetDespawnLocation);
	}
}

void ACustomerAIController::SetTableLocation()
{
	auto result = MoveToLocation(Customer->GetTableLocation(), 10.f);
	GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &ACustomerAIController::OnMoveToTableFinished);
	UE_LOG(LogTemp, Warning, TEXT("moveto: %s"), *UEnum::GetValueAsString(result));
}

void ACustomerAIController::SetDespawnLocation()
{
	MoveToLocation(Customer->GetDespawnLocation(), 100.f);
	GetPathFollowingComponent()->OnRequestFinished.AddUObject(Customer, &ACustomer::OnMoveToDespawnFinished);
}

void ACustomerAIController::OnMoveToTableFinished(FAIRequestID ID, const FPathFollowingResult& Result)
{
	if (Result.IsSuccess())
	{
		if (ANoTimeToWaitGameMode* GameMode = Cast<ANoTimeToWaitGameMode>(UGameplayStatics::GetGameMode(this)))
		{
			Customer->GetTable()->GetTagHandler()->AddTag(NTTWGameplayTags::TAG_Table_Customer_WaitingForMenu);
			GetWorld()->GetTimerManager().SetTimer(Customer->TimerHandle, Customer, &ACustomer::Leave, GameMode->GetCustomerType(Customer->GetCustomerTypeTag()).ServingTime);
		}
	}
}