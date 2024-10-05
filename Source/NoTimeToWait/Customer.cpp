// Fill out your copyright notice in the Description page of Project Settings.


#include "Customer.h"

#include "NTTWGameplayTags.h"
#include "TagHandlerComponent.h"
#include "CustomerSpawnerComponent.h"
#include "NoTimeToWaitGameMode.h"
#include "Table.h"
#include "TimerManager.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "TimerHandlerComponent.h"

// Sets default values
ACustomer::ACustomer() : CustomerTypeTag(NTTWGameplayTags::TAG_Customer_Normal)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TagHandler = CreateDefaultSubobject<UTagHandlerComponent>("Tag Handler");

	GameMode = Cast<ANoTimeToWaitGameMode>(UGameplayStatics::GetGameMode(this));

	Money = 0.f;
}

// Called when the game starts or when spawned
void ACustomer::BeginPlay()
{
	Super::BeginPlay();

	Type = GameMode->GetCustomerType(CustomerTypeTag);
}

// Called every frame
void ACustomer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACustomer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FGameplayTag ACustomer::GetFoodType() const
{
	return FoodType;
}

void ACustomer::SetFoodType(const FGameplayTag& TypeTag)
{
	FoodType = TypeTag;
	TagHandler->AddTag(TypeTag);
}

ATable* ACustomer::GetTable() const
{
	return Table;
}

void ACustomer::SetTable(ATable* CustomerTable)
{
	Table = CustomerTable;
	TableLocation = Table->GetSeatLocation();
	Table->OnReceivedMenuDelegate.AddUObject(this, &ACustomer::OnReceivedMenu);
	OnCustomerSpawnedDelegate.ExecuteIfBound();
}

FVector ACustomer::GetTableLocation() const
{
	return TableLocation;
}

FVector ACustomer::GetDespawnLocation() const
{
	return DespawnLocation;
}

void ACustomer::SetDespawnLocation(const FVector& Location)
{
	DespawnLocation = Location;
}

FGameplayTag ACustomer::GetCustomerTypeTag() const
{
	return CustomerTypeTag;
}

void ACustomer::SetCustomerType(const FGameplayTag& TypeTag)
{
	CustomerTypeTag = TypeTag;
}

void ACustomer::OnReceivedMenu()
{
	TotalRemainingTime += GetWorld()->GetTimerManager().GetTimerRemaining(TimerHandle);
	if (GameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("Received Menu: %f"), Type.ServingTime)
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACustomer::Leave, Type.ServingTime);
	}
}

void ACustomer::OnReceivedFood()
{
	TotalRemainingTime += GetWorld()->GetTimerManager().GetTimerRemaining(TimerHandle);
	CalculateMoney(TotalRemainingTime);
	UE_LOG(LogTemp, Warning, TEXT("Received Food: %f"), Type.EatingTime);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACustomer::Leave, Type.EatingTime);
}

void ACustomer::Leave()
{
	OnCustomerFinishedDelegate.ExecuteIfBound();
}

void ACustomer::Despawn()
{
	Destroy();
}

void ACustomer::OnMoveToDespawnFinished(FAIRequestID ID, const FPathFollowingResult& Result)
{
	Despawn();
}

void ACustomer::CalculateMoney(const float RemainingTime)
{
	// Time based tip + minimum customer money
	Money += (RemainingTime / (Type.ServingTime + Type.MenuTime)) * (Type.Money / 2) + Type.Money;
	GameMode->UpdatePlayerMoney(Money);
}