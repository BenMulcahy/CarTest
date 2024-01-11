// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomVehicleController.generated.h"

/**
 * 
 */

class UInputAction; //Define input action class so dont have to define it as class every input

UCLASS()
class CARTEST_API ACustomVehicleController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACustomVehicleController();


protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;


#pragma region Variables
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		TObjectPtr<class ACustomVehiclePawn> playerVehicle;


#pragma endregion


#pragma region Inputs
protected:
	UFUNCTION(BlueprintCallable)
		void DoAccelerate(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
		void DoBrake(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
		void DoTurn(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
		void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
		void ChangeCamera();

public:
	/* Mapping Context */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputMappingContext> MappingContext;

	/* Accelerate IA */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> AccelerateAction;

	/* Brake IA */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> BrakeAction;

	/* Turn IA */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> SteerAction;

	/* Change Camera IA */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> ChangeCameraAction;

	/* Camera Look */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> CameraLookAction;

#pragma endregion
};
