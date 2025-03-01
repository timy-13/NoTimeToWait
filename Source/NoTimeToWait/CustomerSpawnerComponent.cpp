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

	TableManager = CreateDefaultSubobject<UTableManagerSubsystem>("Table Manager");
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
		// SpawnCustomers(GameMode->GetDifficulty());

		// Start spawning with initial delay
		const float InitialDelay = FMath::RandRange(3.0f, 8.0f);
		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &UCustomerSpawnerComponent::SpawnCustomers, InitialDelay, false);
	}
}

void UCustomerSpawnerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
    
	// Clean up timers when component stops
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(RetrySpawnHandle);
}

// Called every frame
void UCustomerSpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCustomerSpawnerComponent::SpawnCustomers()
{
	// DifficultyLevel.CustomerNumber;


	if (!TableManager)
	{
		UE_LOG(LogTemp, Error, TEXT("TableManager is null!"));
		return;
	}

	if (ATable* Table = TableManager->GetRandomEmptyTable())
	{
		TableManager->RemoveEmptyTable(Table);
		SpawnCustomer(Table, NTTWGameplayTags::TAG_Food_Bread);

		// Schedule next spawn with variable interval
		const float NextSpawnDelay = FMath::RandRange(8.0f, 15.0f);
		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &UCustomerSpawnerComponent::SpawnCustomers, NextSpawnDelay, false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No empty tables - retrying in 10 seconds"));
		
		// Retry after delay if no tables available
		GetWorld()->GetTimerManager().SetTimer(RetrySpawnHandle, this, &UCustomerSpawnerComponent::SpawnCustomers, 10.0f, false);
	}
}

void UCustomerSpawnerComponent::SpawnCustomer(ATable* Table, const FGameplayTag& FoodType) const
{

	ACustomer* Customer = GetWorld()->SpawnActor<ACustomer>(CustomerClass, GetComponentLocation(), GetOwner()->GetActorRotation());

	Customer->SetTable(Table);
	Customer->SetFoodType(FoodType);
	Customer->SetDespawnLocation(GetComponentLocation());

	Table->SetCustomer(Customer);
}