// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerSpawnerComponent.h"

#include "Customer.h"
#include "Table.h"
#include "NoTimeToWaitGameMode.h"
#include "NTTWGameplayTags.h"
#include "TableManagerSubsystem.h"

#include "GameplayTags.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCustomerSpawnerComponent::UCustomerSpawnerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCustomerSpawnerComponent::BeginPlay()
{
	Super::BeginPlay();
	TableManager = GetWorld()->GetSubsystem<UTableManagerSubsystem>();
	TableManager->SetTableClass(TableClass);
	TableManager->InitializeEmptyTables();

	if (ANoTimeToWaitGameMode* GameMode = Cast<ANoTimeToWaitGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		SpawnCustomers(GameMode->GetDifficulty());
	}
}


// Called every frame
void UCustomerSpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCustomerSpawnerComponent::SpawnCustomers(const Difficulty& DifficultyLevel)
{
	DifficultyLevel.CustomerNumber;

	// algorithm to spawn customers at certain intervals

	if (ATable* Table = TableManager->GetRandomEmptyTable())
	{
		TableManager->RemoveEmptyTable(Table);
		SpawnCustomer(Table, NTTWGameplayTags::TAG_Food_Bread);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No empty tables"));
		// wait if there are no empty tables
	}
}

void UCustomerSpawnerComponent::SpawnCustomer(ATable* Table, const FGameplayTag& FoodType)
{
	ACustomer* Customer = GetWorld()->SpawnActor<ACustomer>(CustomerClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());

	Customer->SetTable(Table);
	Customer->SetFoodType(FoodType);
	Customer->SetDespawnLocation(GetOwner()->GetActorLocation());

	Table->SetCustomer(Customer);
}