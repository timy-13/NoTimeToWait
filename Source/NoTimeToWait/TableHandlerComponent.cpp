// Fill out your copyright notice in the Description page of Project Settings.


#include "TableHandlerComponent.h"

#include "Table.h"
#include "EngineUtils.h"

void UTableHandlerComponent::InitializeTableArray()
{
	GetAllTables(GetWorld(), EmptyTables);
}

ATable* UTableHandlerComponent::GetRandomEmptyTable()
{
	if (EmptyTables.Num() > 0)
	{
		int RandomIndex = FMath::RandRange(0, EmptyTables.Num() - 1);
		return EmptyTables[RandomIndex];
	}

	return nullptr;
}

void UTableHandlerComponent::AddEmptyTable(ATable* Table)
{
	EmptyTables.AddUnique(Table);
}

void UTableHandlerComponent::RemoveEmptyTable(ATable* Table)
{
	EmptyTables.RemoveSingle(Table);
}

void UTableHandlerComponent::GetAllTables(UWorld* World, TArray<ATable*>& OutTables)
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
	