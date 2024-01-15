// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "CustomVehiclePawn.generated.h"

/**
 * 
 */

class UCameraComponent;

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
	void Handbrake(bool InputValue);
	/// <summary>
	/// Populate all cameras on vehicle
	/// </summary>
	/// <returns>Array of UCameraComponent Pointers</returns>
	TArray<TObjectPtr<UCameraComponent>> GetVehicleCameras();
	TObjectPtr<UCameraComponent> GetActiveCamera();
	
#pragma endregion

#pragma region Variables and Components
public:

private:
	float CachedMaxRPM = 7500.f; //Used to store max rpm when not in reverse

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera | SpringArm")
		TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera | Chase Camera")
		TObjectPtr<UCameraComponent> ChaseCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera | Hood Camera")
		TObjectPtr<UCameraComponent> HoodCamera;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera | Cockpit Camera")
		TObjectPtr<UCameraComponent> CockpitCamera;

	UPROPERTY(BlueprintReadOnly, Category = "Vehicle")
		TObjectPtr<class UChaosWheeledVehicleMovementComponent> Vehicle;

	UPROPERTY(BlueprintReadOnly, Category =  "Camera")
		TArray<TObjectPtr<UCameraComponent>> VehicleCameras;

#pragma endregion

};
