// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagAssetInterface.h"
#include "TagHandlerComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NOTIMETOWAIT_API UTagHandlerComponent : public UActorComponent, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTagHandlerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	FGameplayTagContainer GetOwnedGameplayTags() const;
	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;
	bool HasExactMatchingGameplayTag(FGameplayTag TagToCheck) const;
	bool HasAnyExactMatchingGameplayTag(const FGameplayTagContainer& TagContainer) const;
	virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	void AddTag(const FGameplayTag& Tag);
	bool RemoveTag(const FGameplayTag& Tag);

private:
	UPROPERTY(EditAnywhere, Category = "Tags")
	FGameplayTagContainer Tags;
};
