// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "Table.generated.h"

class UBoxComponent;
class UTagHandlerComponent;
class ACustomer;
class AKitchen;

DECLARE_MULTICAST_DELEGATE(FOnReceivedMenuSignature);

UCLASS()
class NOTIMETOWAIT_API ATable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATable();

	FOnReceivedMenuSignature OnReceivedMenuDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddRequiredFood(const FGameplayTag& FoodType);

	void Reset();

	void SetCustomer(ACustomer* TableCustomer);

	void OnReceivedMenu();

	void Clean();

	UTagHandlerComponent* GetTagHandler() const;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> TableMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTagHandlerComponent> TagHandler;

	UFUNCTION()
	void OnInteractionComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	void OnCustomerLeave();

	TObjectPtr<AActor> ServedObject;

	UPROPERTY(VisibleAnywhere, Category = "Food")
	FGameplayTagContainer OrderedFoodTags;

	TObjectPtr<ACustomer> Customer;

	UPROPERTY(EditAnywhere, Category = "Food")
	TObjectPtr<AKitchen> Kitchen;
};
