// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TableHandlerComponent.generated.h"

class ATable;

/**
 * 
 */
UCLASS()
class NOTIMETOWAIT_API UTableHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// hold table objects
	// add
	// remove
	// update
	void InitializeTableArray();

	ATable* GetRandomEmptyTable();

	void AddEmptyTable(ATable* Table);
	void RemoveEmptyTable(ATable* Table);

private:
	void GetAllTables(UWorld* World, TArray<ATable*>& OutTables);

	// update gameplay tags of table??
	// should this be done in the table itself?
	UPROPERTY(EditAnywhere, Category = "Tables")
	TArray<ATable*> EmptyTables;
	
	UPROPERTY(EditAnywhere, Category = "Tables")
	TSubclassOf<ATable> TableClass;

	// maybe i just hold the array of tables inside the spawner, gameplay tag updates will be done by the table itself
};
