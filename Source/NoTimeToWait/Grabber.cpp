// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "NTTWGameplayTags.h"
#include "TagHandlerComponent.h"
#include "Table.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	MaxRange = 100.f;
	GrabRadius = 42.f;
	GrabHalfHeight = 96.f;
	HoldDistance = 50.f;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MovePhysicsHandle();
}

bool UGrabber::IsInRange(FHitResult& HitResult, ECollisionChannel TraceChannel)
{
	FVector Start = GetOwner()->GetActorLocation();
	FVector End = Start + GetOwner()->GetActorForwardVector() * MaxRange;

	DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	return GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, TraceChannel, FCollisionShape::MakeCapsule(GrabHalfHeight, GrabRadius));
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	FHitResult HitResult;
	if (IsInRange(HitResult, ECC_GameTraceChannel1))
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->SetSimulatePhysics(true);
		HitComponent->WakeAllRigidBodies();
		DrawDebugCapsule(GetWorld(), HitResult.Location, GrabHalfHeight, GrabRadius, FQuat::Identity, FColor::Blue, false, 10);

		AActor* HitActor = HitResult.GetActor();
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitActor->GetActorNameOrLabel());
		if (UActorComponent* TagHandler = HitActor->FindComponentByClass(UTagHandlerComponent::StaticClass()))
		{
			Cast<UTagHandlerComponent>(TagHandler)->AddTag(NTTWGameplayTags::TAG_Interaction_Grabbed);
			Cast<UTagHandlerComponent>(TagHandler)->RemoveTag(NTTWGameplayTags::TAG_Interaction_NotGrabbed);
		}
		/*UTagHandlerComponent* TagHandler = PhysicsHandle->GetGrabbedComponent()->GetOwner()->FindComponentByClass<UTagHandlerComponent>();
		if (TagHandler)
		{
			TagHandler->RemoveTag(NTTWGameplayTags::TAG_Interaction_NotGrabbed);
			TagHandler->AddTag(NTTWGameplayTags::TAG_Interaction_Grabbed);
		}*/

		HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, HitResult.ImpactPoint, GetOwner()->GetActorRotation());
	}
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr) {
		return;
	}

	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		if (UActorComponent* TagHandler = PhysicsHandle->GetGrabbedComponent()->GetOwner()->FindComponentByClass(UTagHandlerComponent::StaticClass()))
		{
			Cast<UTagHandlerComponent>(TagHandler)->AddTag(NTTWGameplayTags::TAG_Interaction_NotGrabbed);
			Cast<UTagHandlerComponent>(TagHandler)->RemoveTag(NTTWGameplayTags::TAG_Interaction_Grabbed);
		}
		//UTagHandlerComponent* TagHandler = PhysicsHandle->GetGrabbedComponent()->GetOwner()->FindComponentByClass<UTagHandlerComponent>();
		//if (TagHandler)
		//{
		//	TagHandler->AddTag(NTTWGameplayTags::TAG_Interaction_NotGrabbed);
		//	TagHandler->RemoveTag(NTTWGameplayTags::TAG_Interaction_Grabbed);
		//}
		PhysicsHandle->ReleaseComponent();
	}
}

void UGrabber::Interact()
{
	FHitResult HitResult;
	if (IsInRange(HitResult, ECC_GameTraceChannel2))
	{
		AActor* HitActor = HitResult.GetActor();
		if (ATable* Table = Cast<ATable>(HitActor))
		{
			if (Table->GetTagHandler()->HasExactMatchingGameplayTag(NTTWGameplayTags::TAG_Table_Customer_WaitingForMenu)) // menu
			{
				Table->OnReceivedMenu();
			}
			else if (Table->GetTagHandler()->HasExactMatchingGameplayTag(NTTWGameplayTags::TAG_Table_Dirty))
			{
				// clean table
				Table->Clean();
				// Cast<Character>(GetOwner())->cleanAnimation
			}
		}
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!Result)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber requires a UPhysicsHandleComponent"));
	}
	return Result;
}

void UGrabber::SetGrabHalfHeight(const float& HalfHeight)
{
	GrabHalfHeight = HalfHeight;
}

void UGrabber::SetGrabRadius(const float& Radius)
{
	GrabRadius = Radius;
}

void UGrabber::MovePhysicsHandle()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	if (PhysicsHandle->GetGrabbedComponent() != nullptr) {
		FVector TargetLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetOwner()->GetActorRotation());
	}
}