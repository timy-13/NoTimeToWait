// Fill out your copyright notice in the Description page of Project Settings.


#include "Table.h"

#include "Components/BoxComponent.h"
#include "TagHandlerComponent.h"
#include "NTTWGameplayTags.h"
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

	RequiredInteractionTags.AddTag(NTTWGameplayTags::TAG_Food);
	RequiredInteractionTags.AddTag(NTTWGameplayTags::TAG_Interaction_NotGrabbed);
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
	UTagHandlerComponent* ActorTagHandler = OtherActor->FindComponentByClass<UTagHandlerComponent>();
	if (ActorTagHandler && ActorTagHandler->HasAllMatchingGameplayTags(RequiredInteractionTags))
	{
		ServedObject = OtherActor;
		bool attach = OtherComp->AttachToComponent(TableMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("FoodSocket"));
	}
}

void ATable::OnCustomerLeave()
{
	ServedObject->Destroy();
}