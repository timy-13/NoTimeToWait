// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerHandlerComponent.h"
#include "NoTimeToWaitGameMode.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTimerHandlerComponent::UTimerHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTimerHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTimerHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTimerHandlerComponent::StartTimer(FString Type)
{
	if (ANoTimeToWaitGameMode* GameMode = Cast<ANoTimeToWaitGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		// start timer based on difficulty and the timer type
		GameMode->GetDifficulty();

	}
}
