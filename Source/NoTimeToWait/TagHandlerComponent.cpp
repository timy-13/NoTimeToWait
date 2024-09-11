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

FGameplayTagContainer UTagHandlerComponent::GetOwnedGameplayTags() const
{
	return Tags;
}

bool UTagHandlerComponent::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	return Tags.HasTag(TagToCheck);
}

bool UTagHandlerComponent::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return Tags.HasAll(TagContainer);
}

bool UTagHandlerComponent::HasExactMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	return Tags.HasTagExact(TagToCheck);
}

bool UTagHandlerComponent::HasAnyExactMatchingGameplayTag(const FGameplayTagContainer& TagContainer) const
{
	return Tags.HasAnyExact(TagContainer);
}

void UTagHandlerComponent::AddTag(const FGameplayTag& Tag)
{
	Tags.AddTag(Tag);
}

bool UTagHandlerComponent::RemoveTag(const FGameplayTag& Tag)
{
	return Tags.RemoveTag(Tag);
}