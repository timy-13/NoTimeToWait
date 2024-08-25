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

	InitializeFoodClassMap();
}

// Called when the game starts or when spawned
void AKitchen::BeginPlay()
{
	Super::BeginPlay();
	
	OnCustomerOrder(FoodClassMap[NTTWGameplayTags::TAG_Food_Bread]);
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

void AKitchen::OnCustomerOrder(TSubclassOf<AFood> Food)
{
	GetWorld()->SpawnActor<AFood>(Food, GetActorLocation() + FVector(0, 0, 50.f), GetActorRotation());
}

