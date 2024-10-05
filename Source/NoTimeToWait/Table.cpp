// Fill out your copyright notice in the Description page of Project Settings.


#include "Table.h"

#include "TagHandlerComponent.h"
#include "NTTWGameplayTags.h"
#include "Customer.h"
#include "Kitchen.h"
#include "Food.h"
#include "TableManagerSubsystem.h"

#include "Components/BoxComponent.h"
#include "GameplayTags.h"

// Sets default values
ATable::ATable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Table Mesh"));
	RootComponent = TableMesh;

	// interaction comp should be on top of the table (and slightly peeking over the edge), so it can take objects
	InteractionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Component"));
	InteractionComponent->SetupAttachment(TableMesh);

	TagHandler = CreateDefaultSubobject<UTagHandlerComponent>(TEXT("Tag Handler"));
	TagHandler->AddTag(NTTWGameplayTags::TAG_Table_Empty);
}

// Called when the game starts or when spawned
void ATable::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATable::OnInteractionComponentOverlap);
}

// Called every frame
void ATable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATable::OnInteractionComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (AFood* Food = Cast<AFood>(OtherActor))
	{
		if (TagHandler->HasExactMatchingGameplayTag(NTTWGameplayTags::TAG_Table_Empty) && Food->GetTagHandler()->HasAnyExactMatchingGameplayTag(OrderedFoodTags))
		{
			ServedObject = OtherActor;
			OrderedFoodTags.RemoveTags(Food->GetTagHandler()->GetOwnedGameplayTags()); // remove the fulfilled food type
			bool attach = OtherComp->AttachToComponent(TableMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("FoodSocket"));
			Customer->OnReceivedFood();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Table must be empty/Must be correct food. CustomerFood: %s, OrderedTag: %s"), *Customer->GetFoodType().GetTagName().ToString(), *OrderedFoodTags.First().GetTagName().ToString());
		}
	}
}

void ATable::AddRequiredFood(const FGameplayTag& FoodType)
{
	OrderedFoodTags.AddTag(FoodType);
}

void ATable::Reset()
{
	OrderedFoodTags.Reset();
}

void ATable::SetCustomer(ACustomer* TableCustomer)
{
	Customer = TableCustomer;
}

void ATable::OnReceivedMenu()
{
	TagHandler->RemoveTag(NTTWGameplayTags::TAG_Table_Customer_WaitingForMenu);
	OrderedFoodTags.AddTag(Customer->GetFoodType());
	if (Kitchen)
	{
		Kitchen->OnCustomerOrder(Customer->GetFoodType());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Kitchen is not set from Table. Can't spawn food."));
	}
	OnReceivedMenuDelegate.Broadcast();
}

void ATable::OnCustomerLeave()
{
	UTableManagerSubsystem* TableManager = GetWorld()->GetSubsystem<UTableManagerSubsystem>();
	TableManager->AddEmptyTable(this);

	ServedObject->Destroy();
	TagHandler->AddTag(NTTWGameplayTags::TAG_Table_Dirty);
	// add dirty dishes mesh
	Customer = nullptr;
}

void ATable::Clean()
{
	TagHandler->RemoveTag(NTTWGameplayTags::TAG_Table_Dirty);
	TagHandler->AddTag(NTTWGameplayTags::TAG_Table_Empty);
}

UTagHandlerComponent* ATable::GetTagHandler() const
{
	return TagHandler;
}

FVector ATable::GetSeatLocation() const
{
	return SeatLocation;
}

void ATable::SetSeatLocation(const FVector& Location)
{
	SeatLocation = Location;
}