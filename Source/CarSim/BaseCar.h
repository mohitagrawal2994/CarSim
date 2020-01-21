// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseCar.generated.h"

UENUM(Meta = (Bitflags))
enum RotationAxis
{
	XRotation,
	YRotation,
	ZRotation
};

UCLASS()
class CARSIM_API ABaseCar : public AActor
{
	GENERATED_BODY()

	class UTimelineComponent* LeftDoorTimeline;
	class UTimelineComponent* RightDoorTimeline;
	class UTimelineComponent* HoodTimeline;
	class UTimelineComponent* TrunkTimeline;

	//Booleans to control whether meshes can be rotated
	bool CanRotateLeftDoor;
	bool CanRotateRightDoor;
	bool CanRotateHood;
	bool CanRotateTrunk;

	bool IsLeftDoorOpen;
	bool IsRightDoorOpen;
	bool IsHoodOpen;
	bool IsTrunkOpen;

	float CurveFloatValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	//Mesh to hold the parts of the car
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* BaseCarMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* LeftDoorMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* RightDoorMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* HoodMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* TrunkMesh;

	UPROPERTY(EditDefaultsOnly, Category = "BoxComponent")
	class UBoxComponent* LeftDoorOBox;

	UPROPERTY(EditDefaultsOnly, Category = "BoxComponent")
	class UBoxComponent* RightDoorOBox;

	UPROPERTY(EditDefaultsOnly, Category = "BoxComponent")
	class UBoxComponent* TrunkOBox;

	UPROPERTY(EditDefaultsOnly, Category = "BoxComponent")
	class UBoxComponent* HoodOBox;

	//Bool to check whether the car's hood and trunk position are opposite to each other i.e the trunk is in front of the car
	UPROPERTY(EditDefaultsOnly, Category = "MeshDetails")
	bool HoodIsFlipped;

	//Enum properties to store on which axis should the mesh be rotated as it can differ based on the creation of the object
	UPROPERTY(EditDefaultsOnly, Category = "MeshDetails")
	TEnumAsByte<RotationAxis> Door1Rotation;

	UPROPERTY(EditDefaultsOnly, Category = "MeshDetails")
	TEnumAsByte<RotationAxis> Door2Rotation;

	UPROPERTY(EditDefaultsOnly, Category = "MeshDetails")
	TEnumAsByte<RotationAxis> HoodRotation;

	UPROPERTY(EditDefaultsOnly, Category = "MeshDetails")
	TEnumAsByte<RotationAxis> TrunkRotation;

	//Curves to hold the aniation playback time and door rotation axis setting
	UPROPERTY(EditDefaultsOnly, Category = "Curves")
	class UCurveFloat* DoorCurve;

	UPROPERTY(EditDefaultsOnly, Category = "Curves")
	class UCurveFloat* HoodCurve;

	UPROPERTY(EditDefaultsOnly, Category = "Curves")
	class UCurveFloat* TrunkCurve;

	// Sets default values for this actor's properties
	ABaseCar();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Function that gets called each frame based on Door curve for Door1
	UFUNCTION()
	void ControlLeftDoor();

	//Function that gets called after the Doorcurve is complete for Door1
	UFUNCTION()
	void SetLeftDoorState();

	//Function that gets called each frame based on Door curve for Door2
	UFUNCTION()
	void ControlRightDoor();

	//Function that gets called after the Doorcurve is complete for Door2
	UFUNCTION()
	void SetRightDoorState();

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

	//UFUNCTION(NetMulticast)
	void ToogleLeftDoor();

	//UFUNCTION(NetMulticast)
	void ToogleRightDoor();

	//UFUNCTION(NetMulticast)
	void ToggleHood();

	//UFUNCTION(NetMulticast)
	void ToggleTrunk();
};
