// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomVehicleController.h"
#include "CustomVehiclePawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Gameframework/SpringArmComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"


ACustomVehicleController::ACustomVehicleController()
{

}

void ACustomVehicleController::BeginPlay()
{
    Super::BeginPlay();

    if (playerVehicle = Cast<ACustomVehiclePawn>(GetPawn())); //ptr to custom vehicle pawn
    else { UE_LOG(LogPlayerController, Error, TEXT("No Vehicle Pawn")); return; }

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        UE_LOG(LogPlayerController, Display, TEXT("Mapping Context Set"));
        Subsystem->AddMappingContext(MappingContext, 0);
    } 
   
     CurrentCamera = playerVehicle->GetActiveCamera();
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
        EInputComponent->BindAction(CameraLookActionController, ETriggerEvent::Triggered, this, &ACustomVehicleController::ControllerLook);

        //Change Camera
        EInputComponent->BindAction(ChangeCameraAction, ETriggerEvent::Triggered, this, &ACustomVehicleController::ChangeCamera);

        //Handbrake
        EInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Triggered, this, &ACustomVehicleController::DoHandbrake);

        //Mouse Look
        EInputComponent->BindAction(CameraLookActionMouse, ETriggerEvent::Triggered, this, &ACustomVehicleController::MouseLook);

        //Controller Look
        EInputComponent->BindAction(CameraLookActionController, ETriggerEvent::Triggered, this, &ACustomVehicleController::ControllerLook);

        UE_LOG(LogPlayerController, Warning, TEXT("Player Input Setup Complete"));
    }

    else UE_LOG(LogPlayerController, Error, TEXT("No Enhanced Input Component found!"));

    
}


//TODO: Does this need to tick?
void ACustomVehicleController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, FString::Printf(TEXT("Current Camera: %s"), CurrentCamera ? *CurrentCamera.GetName() : TEXT("Null")));

    //TODO: Implement camera reset after no input for a short while
    /*
    if (!bCameraInput)
    {
        ResetCamera();
    }
    */
}

//TODO: Implement
bool ACustomVehicleController::CanCameraFreeMove()
{
    if (true)
    {
        return true;
    }
   
    return false;
 
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

void ACustomVehicleController::DoHandbrake(const FInputActionValue& Value)
{
    playerVehicle->Handbrake(Value.Get<bool>());
}


/**       CAMERA CONTROLS            **/

void ACustomVehicleController::ChangeCamera()
{
    if (!CurrentCamera) { UE_LOG(LogPlayerController, Error, TEXT("No Current Camera")); return; }

    UE_LOG(LogPlayerController, Warning, TEXT("Change Camera Input"));
    
    int16 fromCameraIndex = playerVehicle->GetVehicleCameras().Find(CurrentCamera); //Get current camera index in vehicleCameras Array 
    TObjectPtr<UCameraComponent> toCamera = playerVehicle->GetVehicleCameras().IsValidIndex(fromCameraIndex + 1) ? playerVehicle->GetVehicleCameras()[fromCameraIndex + 1] : playerVehicle->GetVehicleCameras()[0]; //Set current camera to next in index if valid else set back to first camera in index


    toCamera->SetActive(true); //enable next cam
    CurrentCamera->SetActive(false); //disable current cam
    CurrentCamera = playerVehicle->GetActiveCamera(); //update current camera - Use GetActiveCamera instead of hard set toCamera for redundency
}


void ACustomVehicleController::ControllerLook(const FInputActionValue& Value)
{
    /* Controller */
    
    //Turn
    playerVehicle->AddControllerYawInput(Value.Get<FVector2D>().X * (ControllerLookXRate * 10) * GetWorld()->GetDeltaSeconds());

    bCameraInput = true;
}


void ACustomVehicleController::ResetCamera()
{
    //Set Controller Yaw and Pitch to Fwd
    playerVehicle->GetController()->SetControlRotation(playerVehicle->GetActorRotation());
}

void ACustomVehicleController::MouseLook(const FInputActionValue& Value)
{
    if (Value.Get<float>() != 0)
    {
        playerVehicle->AddControllerYawInput(Value.Get<FVector2D>().X);
    }

    bCameraInput = true;
}

void ACustomVehicleController::LookBehind()
{

}

#pragma endregion