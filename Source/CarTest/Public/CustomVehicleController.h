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


private:
	/// <summary>
	/// Determines if camera can free rotate around vehicle or snaps to L/R/Behind when look input recieved
	/// </summary>
	/// <returns>True if can free move</returns>
	bool IsCameraInput();
	void UpdateCameraResetTimer();

#pragma region Variables

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		TObjectPtr<class ACustomVehiclePawn> playerVehicle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera | Controller", meta = (ClampMin = "0", UIMin = "0"))
		float ControllerLookXRate = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera | Controller", meta = (ClampMin = "0", UIMin = "0"))
		float ControllerLookYRate = 5.f;

	/// <summary>
	/// Current Camera used by player
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
		TObjectPtr<class UCameraComponent> CurrentCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera" , meta = (ClampMin = "0.25", UIMin = "0.25", DisplayName = "Camera Reset Timer"))
		float TimeToCameraReset = 0.5f;

private:
	bool bCameraInput = false;
	float CameraResetTimer = 0.f;
	bool bLookBack = false;
	TObjectPtr<struct FEnhancedInputActionValueBinding> MouseLookBindingValue;
	 TObjectPtr<struct FEnhancedInputActionValueBinding> ControllerLookBindingValue;

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
		void DoHandbrake(const FInputActionValue& Value);

	/// <summary>
	/// Reset Current Camera to default position
	/// </summary>
	UFUNCTION(BlueprintCallable)
		void ResetCamera();


	/// <summary>
	/// Camera movement
	/// </summary>
	/// <param name="Value"></param>
	UFUNCTION(BlueprintCallable)
		void ControllerLook(const FInputActionValue& Value);
	
	/// <summary>
	/// Mouse Camera Movement
	/// </summary>
	/// <param name="Value"></param>
	UFUNCTION(BlueprintCallable)
		void MouseLook(const FInputActionValue& Value);

	/// <summary>
	/// Snap Camera to look backwards
	/// </summary>
	UFUNCTION(BlueprintCallable)
		void LookBehind(const FInputActionValue& Value);


	/// <summary>
	/// Cycle between available vehicle cameras
	/// </summary>
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

	/* Handbrake IA */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> HandbrakeAction;

	/* Turn IA */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> SteerAction;

	/* Change Camera IA */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> ChangeCameraAction;

	/* Camera Look */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> CameraLookActionController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> CameraLookActionMouse;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> LookBehindAction;

#pragma endregion
};
