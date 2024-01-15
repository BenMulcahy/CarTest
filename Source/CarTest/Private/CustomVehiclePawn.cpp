// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomVehiclePawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ChaosWheeledVehicleMovementComponent.h"

//TODO: Rev limiter on Reverse

ACustomVehiclePawn::ACustomVehiclePawn()
{   
   Vehicle = CastChecked<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement()); //Save pointer to vehicle movement component
   UMeshComponent* VehicleMesh = CastChecked<UMeshComponent>(GetMesh()); //Save pointer to vehicle mesh

#pragma region BaseVehicleSetup
   VehicleMesh->SetSimulatePhysics(true);

   //TODO: Default Engine Settings
   //Default Torque Setup -> Based on MR2 Test to achieve near real world results (its close enough)
   Vehicle->EngineSetup.MaxRPM = 7500.0f;
   Vehicle->EngineSetup.MaxTorque = 166.0f;
   Vehicle->EngineSetup.EngineRevDownRate = 2400.0f;
   Vehicle->EngineSetup.EngineIdleRPM = 1200.0f;
   Vehicle->EngineSetup.TorqueCurve.GetRichCurve()->Reset();
   Vehicle->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(1200.0f, 125.0f);
   Vehicle->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(3200.0f, 166.0f);
   Vehicle->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(4400.0f, 169.0f);
   Vehicle->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(4800.0f, 175.0f);
   Vehicle->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(6000.0f, 140.0f);
   Vehicle->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(7500.0f, 0.0f);

   //Default Steering Setup
   Vehicle->SteeringSetup.SteeringCurve.GetRichCurve()->Reset();
   Vehicle->SteeringSetup.SteeringCurve.GetRichCurve()->AddKey(0.0f, 1.0f);
   Vehicle->SteeringSetup.SteeringCurve.GetRichCurve()->AddKey(60.0f, 0.83f);
   Vehicle->SteeringSetup.SteeringCurve.GetRichCurve()->AddKey(100.0f, 0.6f);

   //Default Transmission Setup
   Vehicle->TransmissionSetup.ForwardGearRatios.Reset();
   Vehicle->TransmissionSetup.ForwardGearRatios.Add(4.85f);
   Vehicle->TransmissionSetup.ForwardGearRatios.Add(3.72f);
   Vehicle->TransmissionSetup.ForwardGearRatios.Add(2.56f);
   Vehicle->TransmissionSetup.ForwardGearRatios.Add(1.66f);
   Vehicle->TransmissionSetup.ForwardGearRatios.Add(1.22f);

   Vehicle->TransmissionSetup.ReverseGearRatios.Reset();
   Vehicle->TransmissionSetup.ReverseGearRatios.Add(1.22f);


   Vehicle->TransmissionSetup.TransmissionEfficiency = 1.0f;
   Vehicle->TransmissionSetup.bUseAutomaticGears = true;
   Vehicle->TransmissionSetup.GearChangeTime = 0.08f;
   Vehicle->TransmissionSetup.ChangeUpRPM = 6300.0f;
   Vehicle->TransmissionSetup.ChangeDownRPM = 1200.0f;

#pragma endregion

#pragma region CameraSetup
   SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm")); //Create Spring Arm
   SpringArm->SetupAttachment(RootComponent); //Attach to root
   SpringArm->TargetArmLength = 800.0f;

   //Enable spring arm follow lag
   SpringArm->bEnableCameraLag = true;
   SpringArm->bEnableCameraRotationLag = true;
   SpringArm->CameraLagMaxDistance = 220.0f;
   SpringArm->CameraLagSpeed = 5.0f;
   SpringArm->CameraRotationLagSpeed = 10.0f;
   
   //Inherits
   SpringArm->bInheritPitch = false;
   SpringArm->bInheritYaw = true;
   SpringArm->bInheritRoll = false;


   //Setup Chase Camera
   ChaseCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ChaseCam"));
   ChaseCamera->SetupAttachment(SpringArm);
   ChaseCamera->bUsePawnControlRotation = false;
   ChaseCamera->FieldOfView = 110.0f;

   //Setup POV Camera
   CockpitCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CockpitCamera"));
   CockpitCamera->SetupAttachment(RootComponent);
   CockpitCamera->bUsePawnControlRotation = false;
   CockpitCamera->FieldOfView = 110.0f;

   //TODO: Setup Hood Camera
   HoodCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("HoodCamera"));
   HoodCamera->SetupAttachment(RootComponent);
   HoodCamera->bUsePawnControlRotation = false;
   HoodCamera->FieldOfView = 110.0f;

   //TODO: Setup Reverse Camera
   
#pragma endregion
}

void ACustomVehiclePawn::BeginPlay()
{
    Super::BeginPlay();
    CachedMaxRPM = Vehicle->EngineSetup.MaxRPM;    
    GetVehicleCameras(); //populate vehicle cameras array

    //TODO: If not local player, remove camera
}

void ACustomVehiclePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Magenta, FString::Printf(TEXT("Speed: %f, RPM: %f, MaxRPM: %f, Gear: %f"), Vehicle->GetForwardSpeedMPH(), Vehicle->GetEngineRotationSpeed(), Vehicle->GetEngineMaxRotationSpeed(), Vehicle->GetCurrentGear()));
}

void ACustomVehiclePawn::Accelerate(float InputValue)
{
    GetVehicleMovementComponent()->SetThrottleInput(InputValue);
    //UE_LOG(LogTemp, Warning, TEXT("Accellerate! %f"), InputValue);
}

void ACustomVehiclePawn::Brake(float InputValue)
{
    GetVehicleMovementComponent()->SetBrakeInput(InputValue);
    //UE_LOG(LogTemp, Warning, TEXT("Brake! %f"), InputValue);
}

void ACustomVehiclePawn::Steering(float InputValue)
{
    GetVehicleMovementComponent()->SetSteeringInput(InputValue);
    //UE_LOG(LogTemp, Warning, TEXT("Turn! %f"), InputValue);
}

void ACustomVehiclePawn::Handbrake(bool InputValue)
{
    //UE_LOG(LogTemp, Warning, TEXT("HANDBRAKE!"));
    Vehicle->SetHandbrakeInput(InputValue);
}

TArray<TObjectPtr<class UCameraComponent>> ACustomVehiclePawn::GetVehicleCameras()
{
    GetComponents<UCameraComponent>(VehicleCameras);
    //UE_LOG(LogTemp, Warning, TEXT("No. Cameras: %d"), VehicleCameras.Num());

    return VehicleCameras;
}

TObjectPtr<class UCameraComponent> ACustomVehiclePawn::GetActiveCamera()
{
    if (GetVehicleCameras().Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("No Cameras Found!"));
        return NULL;
    }
    else 
    {
        TObjectPtr<UCameraComponent> ActiveCam;

        for (TObjectPtr<UCameraComponent> camera : GetVehicleCameras())
        {
            if (camera->IsActive())
            {
                //UE_LOG(LogTemp, Warning, TEXT("(GetVehicleCamera) Current Camera: %s"), *camera.GetName());
                ActiveCam = camera;
                return ActiveCam;
            }
        }
        return ActiveCam;
    }

}
