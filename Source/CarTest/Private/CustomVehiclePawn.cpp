// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomVehiclePawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ChaosWheeledVehicleMovementComponent.h"

ACustomVehiclePawn::ACustomVehiclePawn()
{
    
   UChaosVehicleMovementComponent* Vehicle = CastChecked<UChaosVehicleMovementComponent>(GetVehicleMovement()); //Save pointer to vehicle movement component
   UMeshComponent* VehicleMesh = CastChecked<UMeshComponent>(GetMesh()); //Save pointer to vehicle mesh

   if (Vehicle == NULL)
   {
       UE_LOG(LogVehicle, Error, TEXT("No Vehicle Component Found!"));
       return;
   }

   if (VehicleMesh == NULL) {
       UE_LOG(LogVehicle, Error, TEXT("No Mesh Component Found!"));
       return;
   }

#pragma region BaseVehicleSetup
   VehicleMesh->SetSimulatePhysics(true);

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

   //TODO: Setup POV Camera

   //TODO: Setup Hood Camera

   //TODO: Setup Reverse Camera
   
#pragma endregion

    
}

void ACustomVehiclePawn::BeginPlay()
{
    Super::BeginPlay();

    //UE_LOG(LogCustomVehicle, Warning, TEXT("%s spawned"), *GetName());


    //TODO: Populate Cameras List

}

void ACustomVehiclePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ACustomVehiclePawn::Accelerate(float InputValue)
{
}

void ACustomVehiclePawn::Brake(float InputValue)
{
}

void ACustomVehiclePawn::Steering(float InputValue)
{
}

void ACustomVehiclePawn::ChangeCamera()
{

}
