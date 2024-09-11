// Fill out your copyright notice in the Description page of Project Settings.


#include "TableManagerSubsystem.h"

#include "Table.h"

#include "EngineUtils.h"

UTableManagerSubsystem::UTableManagerSubsystem()
{
	GetAllTables(GetWorld(), EmptyTables);

}

bool UTableManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    return true;
}

void UTableManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    // Set up any global health-related state

	GetAllTables(GetWorld(), EmptyTables);
}

void UTableManagerSubsystem::Deinitialize()
{
    // Clean up resources
    Super::Deinitialize();
}

void UTableManagerSubsystem::InitializeEmptyTables()
{
	GetAllTables(GetWorld(), EmptyTables);
}

ATable* UTableManagerSubsystem::GetRandomEmptyTable()
{
	if (EmptyTables.Num() > 0)
	{
		int RandomIndex = FMath::RandRange(0, EmptyTables.Num() - 1);
		return EmptyTables[RandomIndex];
	}

	return nullptr;
}

void UTableManagerSubsystem::AddEmptyTable(ATable* Table)
{
	EmptyTables.AddUnique(Table);
}

void UTableManagerSubsystem::RemoveEmptyTable(ATable* Table)
{
	EmptyTables.RemoveSingle(Table);
}

void UTableManagerSubsystem::SetTableClass(const TSubclassOf<ATable>& Class)
{
	TableClass = Class;
}


void UTableManagerSubsystem::GetAllTables(UWorld* World, TArray<ATable*>& OutTables)
{
	OutTables.Reset();

	if (World)
	{
		for (TActorIterator<ATable> It(World, TableClass); It; ++It)
		{
			OutTables.Add(*It);
		}
	}
}