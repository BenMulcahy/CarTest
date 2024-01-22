// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "CustomVehicleCamera.generated.h"

/**
 * 
 */
UCLASS()
class CARTEST_API UCustomVehicleCamera : public UCameraComponent
{
	GENERATED_BODY()

public:
	bool bFreeRotatable = true;


public:
	UFUNCTION(BlueprintCallable)
		bool CanFreeRotate();
};
