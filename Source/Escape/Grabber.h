// Copyright © Emily Peregrine 2016

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

#define OUT

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	UPROPERTY(EditAnywhere)
	float Range = 5.f;
	
	void Grab();
	void Release();

	FVector LineCastToViewpoint();
	void FindPhysicsHandleComponent();
	void FindInputComponent();

	const FHitResult GetFirstPhysicsBodyInReach();

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
};
