// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VRPawn.generated.h"

UCLASS()
class CARSIM_API AVRPawn : public APawn
{
	GENERATED_BODY()

	//Variables to store the instance of the car
	UPROPERTY(Replicated)
	class ABaseCar* MyCar;
	TArray<AActor*> FoundCars;

	//Variables to handle teleportation
	bool CanFindTeleportationPoint;
	bool ValidTeleportLocation;
	FNavLocation ValTeleportLocation;
	FVector TeleportLocation;

	//Variables to handle LineTrace
	FHitResult Hit;
	FVector LTraceStart;
	FVector LTraceEnd;

	//Float values to control the animation of the hand skeletal mesh
	float LeftHandState;
	float RightHandState;

protected:
	//Variable to hold the navigation mesh
	class UNavigationSystemV1* MyNavMesh;

	//Variable to store the component with which overlapping
	UPrimitiveComponent* MyOverlappingComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Origin")
	class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Origin")
	class USceneComponent* RootOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	class UCameraComponent* PlayerCamera;

	UPROPERTY(EditDefaultsOnly, Category = "SkeletalMesh")
	class UMotionControllerComponent* LeftHandMC;

	UPROPERTY(EditDefaultsOnly, Category = "SkeletalMesh")
	class UMotionControllerComponent* RightHandMC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SkeletalMesh")
	class USkeletalMeshComponent* LeftHandMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SkeletalMesh")
	class USkeletalMeshComponent* RightHandMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SkeletalMesh")
	class UBoxComponent* LeftHandOBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SkeletalMesh")
	class UBoxComponent* RightHandOBox;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Function for replicated varibales
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	//Function to get and replicate the car
	UFUNCTION(Server, Reliable, WithValidation)
	void GetCar();

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	//Function to perfrom actions on the car
	void Action();

	//Function to set the rotation to go to after teleportation
	void TeleportXAxis(float Value);

	void TeleportYAxis(float Value);

	//Function to set if we can teleport
	void CanFindTelPoint();

	//Function that teleports to the pawn to that location
	void TeleportTo();

public:
	UPROPERTY(EditDefaultsOnly, Category = "LineTrace")
	float LineTraceRange;

	// Sets default values for this pawn's properties
	AVRPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Server, Reliable, WithValidation)
	void AllowToggleCarParts();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void ToggleCarParts();

	UFUNCTION(BlueprintCallable)
	float GetLeftHandState();

	UFUNCTION(BlueprintCallable)
	float GetRightHandState();

	UFUNCTION()
	virtual void OnOverlapBeginLeft(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEndLeft(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	virtual void OnOverlapBeginRight(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEndRight(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};