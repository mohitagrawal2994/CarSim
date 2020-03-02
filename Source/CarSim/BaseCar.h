// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseCar.generated.h"

UENUM(Meta = (Bitflags))
enum RotationAxis
{
	XRotation,
	NegXRotation,
	YRotation,
	NegYRotation,
	ZRotation,
	NegZRotation
};

UCLASS()
class CARSIM_API ABaseCar : public AActor
{
	GENERATED_BODY()

	class UTimelineComponent* LeftFrontDoorTimeline;
	class UTimelineComponent* LeftFrontWindowTimeline;
	class UTimelineComponent* LeftBackDoorTimeline;
	class UTimelineComponent* LeftBackWindowTimeline;
	class UTimelineComponent* RightFrontDoorTimeline;
	class UTimelineComponent* RightFrontWindowTimeline;
	class UTimelineComponent* RightBackDoorTimeline;
	class UTimelineComponent* RightBackWindowTimeline;
	class UTimelineComponent* HoodTimeline;
	class UTimelineComponent* TrunkTimeline;

	//Booleans to control whether meshes can be rotated
	bool CanRotateLeftFrontDoor;
	bool CanRotateLeftFrontWindow;
	bool CanRotateLeftBackDoor;
	bool CanRotateLeftBackWindow;
	bool CanRotateRightFrontDoor;
	bool CanRotateRightFrontWindow;
	bool CanRotateRightBackDoor;
	bool CanRotateRightBackWindow;
	bool CanRotateHood;
	bool CanRotateTrunk;

	bool IsLeftFrontDoorOpen;
	bool IsLeftFrontWindowOpen;
	bool IsLeftBackDoorOpen;
	bool IsLeftBackWindowOpen;
	bool IsRightFrontDoorOpen;
	bool IsRightFrontWindowOpen;
	bool IsRightBackDoorOpen;
	bool IsRightBackWindowOpen;
	bool IsHoodOpen;
	bool IsTrunkOpen;

	float CurveFloatValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	//Bool to check whether the car's hood and trunk position are opposite to each other i.e the trunk is in front of the car
	UPROPERTY(EditDefaultsOnly, Category = "MeshDetails")
	bool HoodIsFlipped;

	//Bool to check if the car has 4 doors
	UPROPERTY(EditDefaultsOnly, Category = "MeshDetails")
	bool Has4Doors;

	//Mesh to hold the parts of the car
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* BaseCarMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* LeftFrontDoorMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* LeftFrontWindowMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* LeftBackDoorMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* LeftBackWindowMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* RightFrontDoorMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* RightFrontWindowMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* RightBackDoorMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* RightBackWindowMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* HoodMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* TrunkMesh;

	UPROPERTY(EditDefaultsOnly, Category = "BoxComponent")
	class UBoxComponent* LeftFrontDoorOBox;

	UPROPERTY(EditDefaultsOnly, Category = "BoxComponent")
	class UBoxComponent* LeftBackDoorOBox;

	UPROPERTY(EditDefaultsOnly, Category = "BoxComponent")
	class UBoxComponent* RightFrontDoorOBox;

	UPROPERTY(EditDefaultsOnly, Category = "BoxComponent")
	class UBoxComponent* RightBackDoorOBox;

	UPROPERTY(EditDefaultsOnly, Category = "BoxComponent")
	class UBoxComponent* TrunkOBox;

	UPROPERTY(EditDefaultsOnly, Category = "BoxComponent")
	class UBoxComponent* HoodOBox;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* SteeringMesh;

	UPROPERTY(EditDefaultsOnly, Category = "BoxComponent")
	class UBoxComponent* SteeringOBox;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* GearMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* LeftFrontWheel;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* LeftBackWheel;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* RightFrontWheel;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* RightBackWheel;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* LeftFrontWheelRim;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* LeftBackWheelRim;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* RightFrontWheelRim;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* RightBackWheelRim;

	UPROPERTY(EditDefaultsOnly, Category = "Array")
	TArray<UStaticMesh*> WheelArray;

	UPROPERTY(EditDefaultsOnly, Category = "Array")
	TArray<UStaticMesh*> RimArray;

	//Enum properties to store on which axis should the mesh be rotated as it can differ based on the creation of the object
	UPROPERTY(EditDefaultsOnly, Category = "MeshDetails")
	TEnumAsByte<RotationAxis> LeftFrontDoorRotation;

	UPROPERTY(EditDefaultsOnly, Category = "MeshDetails")
	TEnumAsByte<RotationAxis> LeftBackDoorRotation;

	UPROPERTY(EditDefaultsOnly, Category = "MeshDetails")
	TEnumAsByte<RotationAxis> RightFrontDoorRotation;

	UPROPERTY(EditDefaultsOnly, Category = "MeshDetails")
	TEnumAsByte<RotationAxis> RightBackDoorRotation;

	UPROPERTY(EditDefaultsOnly, Category = "MeshDetails")
	TEnumAsByte<RotationAxis> HoodRotation;

	UPROPERTY(EditDefaultsOnly, Category = "MeshDetails")
	TEnumAsByte<RotationAxis> TrunkRotation;

	//Curves to hold the aniation playback time and door rotation axis setting
	UPROPERTY(EditDefaultsOnly, Category = "Curves")
	class UCurveFloat* DoorCurve;

	UPROPERTY(EditDefaultsOnly, Category = "Curves")
	class UCurveFloat* WindowXCurve;

	UPROPERTY(EditDefaultsOnly, Category = "Curves")
	class UCurveFloat* WindowZCurve;

	UPROPERTY(EditDefaultsOnly, Category = "Curves")
	class UCurveFloat* HoodCurve;

	UPROPERTY(EditDefaultsOnly, Category = "Curves")
	class UCurveFloat* TrunkCurve;

	// Sets default values for this actor's properties
	ABaseCar();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Function to call front doors Timeline Binding functions
	UFUNCTION()
	void FrontDoorBindFunc();

	//Function to call front Windows Timeline Binding functions
	UFUNCTION()
	void FrontWindowBindFunc();

	//unction that gets called each frame based on Door curve for LeftFrontDoor
	UFUNCTION()
	void ControlLeftFrontDoor();

	//Function that gets called after the Doorcurve is complete for LeftFrontDoor
	UFUNCTION()
	void SetLeftFrontDoorState();

	//Function that gets called each frame based on Door curve for LeftBackDoor
	UFUNCTION()
	void ControlLeftBackDoor();

	//Function that gets called after the Doorcurve is complete for LeftBackDoor
	UFUNCTION()
	void SetLeftBackDoorState();

	//Function that gets called each frame based on Door curve for RightFrontDoor
	UFUNCTION()
	void ControlRightFrontDoor();

	//Function that gets called after the Doorcurve is complete for RightFrontDoor
	UFUNCTION()
	void SetRightFrontDoorState();

	//Function that gets called each frame based on Door curve for RightBackDoor
	UFUNCTION()
	void ControlRightBackDoor();

	//Function that gets called after the Doorcurve is complete for RightBackDoor
	UFUNCTION()
	void SetRightBackDoorState();

	//Function that gets called each frame based on HoodCurve
	UFUNCTION()
	void ControlHood();

	//Function that gets called after the Hoodcurve is complete
	UFUNCTION()
	void SetHoodState();

	//Function that gets called each frame based on Trunk curve
	UFUNCTION()
	void ControlTrunk();

	//Function that gets called after the Trunkcurve is complete
	UFUNCTION()
	void SetTrunkState();

	//Function to switch the rotation axis
	FQuat SwitchAxis(int MyAxis);

	UFUNCTION()
	void ToggleLeftFrontDoor();

	UFUNCTION()
	void ToggleLeftBackDoor();

	UFUNCTION()
	void ToggleRightFrontDoor();

	UFUNCTION()
	void ToggleRightBackDoor();

	UFUNCTION()
	void ToggleHood();

	UFUNCTION()
	void ToggleTrunk();
};