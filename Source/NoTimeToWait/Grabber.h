// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Grabber.generated.h"

class UPhysicsHandleComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NOTIMETOWAIT_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Grab();
	void Release();

	void SetGrabHalfHeight(const float& HalfHeight);
	void SetGrabRadius(const float& Radius);

private:
	bool IsInRange(FHitResult& HitResult);

	UPhysicsHandleComponent* GetPhysicsHandle() const;

	void MovePhysicsHandle();

	UPROPERTY(EditAnywhere, Category = "Grab")
	float MaxRange;

	UPROPERTY(EditAnywhere, Category = "Grab")
	float HoldDistance;

	float GrabHalfHeight;
	float GrabRadius;
};
