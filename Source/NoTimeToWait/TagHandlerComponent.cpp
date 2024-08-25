// Fill out your copyright notice in the Description page of Project Settings.


#include "TagHandlerComponent.h"

#include "GameplayTags.h"

// Sets default values for this component's properties
UTagHandlerComponent::UTagHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UTagHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTagHandlerComponent::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = Tags;
}

bool UTagHandlerComponent::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	return Tags.HasTag(TagToCheck);
}

void UTagHandlerComponent::AddTag(const FGameplayTag& Tag)
{
	Tags.AddTag(Tag);
}

void UTagHandlerComponent::RemoveTag(const FGameplayTag& Tag)
{
	Tags.RemoveTag(Tag);
}