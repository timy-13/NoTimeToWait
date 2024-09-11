// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TableManagerSubsystem.generated.h"

class ATable;

/**
 * 
 */
UCLASS()
class NOTIMETOWAIT_API UTableManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UTableManagerSubsystem();

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	ATable* GetRandomEmptyTable();

	void AddEmptyTable(ATable* Table);
	void RemoveEmptyTable(ATable* Table);

	void SetTableClass(const TSubclassOf<ATable>& Class);

	void InitializeEmptyTables();

private:
	void GetAllTables(UWorld* World, TArray<ATable*>& OutTables);

	UPROPERTY(EditAnywhere, Category = "Tables")
	TArray<ATable*> EmptyTables;

	UPROPERTY(EditAnywhere, Category = "Tables")
	TSubclassOf<ATable> TableClass;
};
