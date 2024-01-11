// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "CustomVehiclePawn.generated.h"

/**
 * 
 */
UCLASS()
class ACustomVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()


#pragma region Functions and Structs
public:

	struct FVehicleDriveState
	{
		int NumWheelsOnGround;
		bool bDrifting;
		bool bReverse;
		bool bStopped;
		bool bVehicleInAir;
	};

	ACustomVehiclePawn();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Accelerate(float InputValue);
	void Brake(float InputValue);
	void Steering(float InputValue);
	void ChangeCamera();
	
#pragma endregion

#pragma region Variables and Components
public:

private:
	TArray<TObjectPtr<class UCameraComponent>> VehicleCameras;
	

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera | SpringArm")
		TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera | Chase Camera")
		TObjectPtr<class UCameraComponent> ChaseCamera;

#pragma endregion

};
