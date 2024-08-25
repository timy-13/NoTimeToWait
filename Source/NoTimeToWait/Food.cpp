// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "Components/BoxComponent.h"
#include "TagHandlerComponent.h"

// Sets default values
AFood::AFood()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>("Collision Component");
	RootComponent = CollisionComp;

	PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>("Plate Mesh");
	PlateMesh->SetupAttachment(RootComponent);

	FoodMesh = CreateDefaultSubobject<UStaticMeshComponent>("Food Mesh");
	FoodMesh->SetupAttachment(PlateMesh, FName("FoodSocket"));

	TagHandlerComponent = CreateDefaultSubobject<UTagHandlerComponent>("Tag Handler Component");
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

