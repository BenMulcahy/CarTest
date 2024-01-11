// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomVehicleController.h"
#include "CustomVehiclePawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ChaosWheeledVehicleMovementComponent.h"


ACustomVehicleController::ACustomVehicleController()
{

}

void ACustomVehicleController::BeginPlay()
{
    Super::BeginPlay();

    if (playerVehicle = Cast<ACustomVehiclePawn>(GetPawn())); //ptr to custom vehicle pawn
    else UE_LOG(LogPlayerController, Error, TEXT("No Vehicle Pawn"));

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        UE_LOG(LogPlayerController, Display, TEXT("Mapping Context Set"));
        Subsystem->AddMappingContext(MappingContext, 0);
    }

}

void ACustomVehicleController::SetupInputComponent()
{
    Super::SetupInputComponent();

    //Bind Inputs
    if (TObjectPtr<UEnhancedInputComponent> EInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {

        //Accel
        EInputComponent->BindAction(AccelerateAction, ETriggerEvent::Triggered, this, &ACustomVehicleController::DoAccelerate);

        //Brake
        EInputComponent->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &ACustomVehicleController::DoBrake);

        //Sterring
        EInputComponent->BindAction(SteerAction, ETriggerEvent::Triggered, this, &ACustomVehicleController::DoTurn);

        //Camera Look
        EInputComponent->BindAction(CameraLookAction, ETriggerEvent::Triggered, this, &ACustomVehicleController::Look);

        UE_LOG(LogPlayerController, Warning, TEXT("Player Input Setup Complete"));
    }
    else UE_LOG(LogPlayerController, Error, TEXT("No Enhanced Input Component found!"));

    
}


//TODO: Does this need to tick?
void ACustomVehicleController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

#pragma region Input Actions

/**       VEHICLE CONTROLS            **/

void ACustomVehicleController::DoAccelerate(const FInputActionValue& Value)
{
    playerVehicle->Accelerate(Value.Get<float>());   
}

void ACustomVehicleController::DoBrake(const FInputActionValue& Value)
{
    playerVehicle->Brake(Value.Get<float>());
}

void ACustomVehicleController::DoTurn(const FInputActionValue& Value)
{
    playerVehicle->Steering(Value.Get<float>());
}


/**       CAMERA CONTROLS            **/

void ACustomVehicleController::ChangeCamera()
{
    UE_LOG(LogPlayerController, Warning, TEXT("Change Camera Input"));
}


void ACustomVehicleController::Look(const FInputActionValue& Value)
{

}

#pragma endregion