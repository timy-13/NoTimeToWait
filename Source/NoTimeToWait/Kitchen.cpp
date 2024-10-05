// Fill out your copyright notice in the Description page of Project Settings.


#include "Kitchen.h"

#include "Food.h"
#include "GameplayTagContainer.h"
#include "NTTWGameplayTags.h"

// Sets default values
AKitchen::AKitchen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CounterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Counter Mesh"));
	RootComponent = CounterMesh;

	bSpawnLocationSet = false;

	InitializeFoodClassMap();
}

// Called when the game starts or when spawned
void AKitchen::BeginPlay()
{
	Super::BeginPlay();
	
	OnCustomerOrder(NTTWGameplayTags::TAG_Food_Bread);
}

// Called every frame
void AKitchen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKitchen::InitializeFoodClassMap()
{
	TSubclassOf<AFood> FoodClass;

	FoodClassMap.Add(NTTWGameplayTags::TAG_Food_Bread, FoodClass);
	FoodClassMap.Add(NTTWGameplayTags::TAG_Food_Watermelon, FoodClass);
}

void AKitchen::OnCustomerOrder(const FGameplayTag& FoodType)
{
	// subscribe to delegate when npc orders food
	// spawn the food that the npc wants

	// spawn location should change as more food is spawned
	// check for empty spots along counter??
	// have several box components, check for an empty one, if none are empty just spawn in the air?
	//Food = GetWorld()->SpawnActor<AFood>(GetActorLocation(), GetActorRotation());

	if (bSpawnLocationSet)
	{
		GetWorld()->SpawnActor<AFood>(FoodClassMap[FoodType], SpawnLocation, GetActorRotation());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Food spawn location is not set"));
	}
}

void AKitchen::SetSpawnLocation(const FVector& Location)
{
	bSpawnLocationSet = true;
	SpawnLocation = Location;
}
