// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include <GameFramework/Actor.h>

#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	//OpenDoor();
	//ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}

void UOpenDoor::OpenDoor() {
	//AActor* Owner = GetOwner();
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor() {
	//AActor* Owner = GetOwner();
	FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);
	Owner->SetActorRotation(NewRotation);
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//pool the trigger volume
	//if the ActorThatOpens is in the volume
	//if (PressurePlate->IsOverlappingActor(ActorThatOpens) ) {
	if ( GetTotalMassOfActorsOnPlate() > 50.f) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	} else {
		CloseDoor();
	}
	if ( GetWorld()->GetTimeSeconds() > LastDoorOpenTime+DoorCloseDelay ) {
		//CloseDoor();
	}
	
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.f;

	//finall all the overlapping actors 
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	//FString names = TEXT(" ");
	for (const auto& Actor : OverlappingActors) {
		//item->GetName();
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Error, TEXT("item: %s"), *Actor->GetName());
		
		
	};
	

	//iterate through them 


	return TotalMass;
}