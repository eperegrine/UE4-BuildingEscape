// Copyright © Emily Peregrine 2016

#include "Escape.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	if (Owner == nullptr) {
		GEngine->AddOnScreenDebugMessage(10, 2.f, FColor::Red, TEXT("There is no Owner"));
	}

	if (PressurePlate == nullptr) {
		GEngine->AddOnScreenDebugMessage(10, 2.f, FColor::Red, TEXT("There is no PressurePlate in the Owner"));
	}
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	float currentTime = GetWorld()->GetTimeSeconds();

	if (GetTotalMassOfActorsOnPlate() >= TriggerMass) {
		OnOpenRequest.Broadcast();
	}
	else {
		OnCloseRequest.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.f;

	if (PressurePlate != nullptr) {
		TArray<AActor*> OverlappingActors;
		PressurePlate->GetOverlappingActors(OUT OverlappingActors);

		for (const AActor* Actor : OverlappingActors) {
			TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}
	
	return TotalMass;
}