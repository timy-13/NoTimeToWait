// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NativeGameplayTags.h"
#include "Food.generated.h"

class UBoxComponent;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Food_Bread);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Food_Watermelon);

UCLASS()
class NOTIMETOWAIT_API AFood : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFood();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* FoodMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PlateMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Food")
	FGameplayTag FoodTag;
};
