// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCar.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Curves/CurveFloat.h"
#include "Components/TimelineComponent.h"

// Sets default values
ABaseCar::ABaseCar()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseCarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseCarMesh"));				//Creating/Assigning MeshComponent to the mesh pointers
	RootComponent = BaseCarMesh;
	BaseCarMesh->SetMobility(EComponentMobility::Static);

	LeftDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoorMesh"));
	LeftDoorMesh->SetupAttachment(RootComponent);
	LeftDoorMesh->SetMobility(EComponentMobility::Movable);

	RightDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoorMesh"));
	RightDoorMesh->SetupAttachment(RootComponent);
	RightDoorMesh->SetMobility(EComponentMobility::Movable);

	TrunkMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrunkMesh"));
	TrunkMesh->SetupAttachment(RootComponent);
	TrunkMesh->SetMobility(EComponentMobility::Movable);

	HoodMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HoodMesh"));
	HoodMesh->SetupAttachment(RootComponent);
	HoodMesh->SetMobility(EComponentMobility::Movable);

	LeftDoorOBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Door1BoxCollider"));		//Assigning a static box component
	LeftDoorOBox->SetupAttachment(RootComponent);
	LeftDoorOBox->SetCollisionProfileName("Trigger");										//Setting its collision preset to be trigger
	LeftDoorOBox->SetMobility(EComponentMobility::Static);

	RightDoorOBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Door2BoxCollider"));		//Assigning a static box component
	RightDoorOBox->SetupAttachment(RootComponent);
	RightDoorOBox->SetCollisionProfileName("Trigger");										//Setting its collision preset to be trigger
	RightDoorOBox->SetMobility(EComponentMobility::Static);

	HoodOBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HoodBoxCollider"));			//Assigning a static box component
	HoodOBox->SetupAttachment(RootComponent);
	HoodOBox->SetCollisionProfileName("Trigger");										//Setting its collision preset to be trigger
	HoodOBox->SetMobility(EComponentMobility::Static);

	TrunkOBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TrunkBoxCollider"));		//Assigning a static box component
	TrunkOBox->SetupAttachment(RootComponent);
	TrunkOBox->SetCollisionProfileName("Trigger");										//Setting its collision preset to be trigger
	TrunkOBox->SetMobility(EComponentMobility::Static);

	HoodIsFlipped = false;

	CanRotateLeftDoor = true;																//Variables to check of the mesh can be rotated i.e. avoids interfering with the mesh if it is being rotated
	CanRotateRightDoor = true;
	CanRotateHood = true;
	CanRotateTrunk = true;

	IsLeftDoorOpen = false;																//Variables to check if the car parts are in opened state
	IsRightDoorOpen = false;
	IsHoodOpen = false;
	IsTrunkOpen = false;

	CurveFloatValue = 0;

}
// Called when the game starts or when spawned
void ABaseCar::BeginPlay()
{
	Super::BeginPlay();

	if (DoorCurve)																					//Checking if the curves exist then binding functions to it
	{
		FOnTimelineFloat Door1Callback;
		FOnTimelineEventStatic Door1FinishedCallback;

		FOnTimelineFloat Door2Callback;
		FOnTimelineEventStatic Door2FinishedCallback;

		Door1Callback.BindUFunction(this, FName("ControlLeftDoor"));
		Door1FinishedCallback.BindUFunction(this, FName("SetLeftDoorState"));

		Door2Callback.BindUFunction(this, FName("ControlRightDoor"));
		Door2FinishedCallback.BindUFunction(this, FName("SetRightDoorState"));

		LeftDoorTimeline = NewObject<UTimelineComponent>(this, FName("Door1Animation"));
		LeftDoorTimeline->AddInterpFloat(DoorCurve, Door1Callback);
		LeftDoorTimeline->SetTimelineFinishedFunc(Door1FinishedCallback);
		LeftDoorTimeline->RegisterComponent();

		RightDoorTimeline = NewObject<UTimelineComponent>(this, FName("Door2Animation"));
		RightDoorTimeline->AddInterpFloat(DoorCurve, Door2Callback);
		RightDoorTimeline->SetTimelineFinishedFunc(Door2FinishedCallback);
		RightDoorTimeline->RegisterComponent();

	}
	if (HoodCurve)
	{
		FOnTimelineFloat HoodCallback;
		FOnTimelineEventStatic HoodFinishedCallback;

		HoodCallback.BindUFunction(this, FName("ControlHood"));
		HoodFinishedCallback.BindUFunction(this, FName("SetHoodState"));

		HoodTimeline = NewObject<UTimelineComponent>(this, FName("HoodAnimation"));
		HoodTimeline->AddInterpFloat(HoodCurve, HoodCallback);
		HoodTimeline->SetTimelineFinishedFunc(HoodFinishedCallback);
		HoodTimeline->RegisterComponent();
	}
	if (TrunkCurve)
	{
		FOnTimelineFloat TrunkCallback;
		FOnTimelineEventStatic TrunkFinishedCallback;

		TrunkCallback.BindUFunction(this, FName("ControlTrunk"));
		TrunkFinishedCallback.BindUFunction(this, FName("SetTrunkState"));

		TrunkTimeline = NewObject<UTimelineComponent>(this, FName("TrunkAnimation"));
		TrunkTimeline->AddInterpFloat(TrunkCurve, TrunkCallback);
		TrunkTimeline->SetTimelineFinishedFunc(TrunkFinishedCallback);
		TrunkTimeline->RegisterComponent();
	}

	
}

// Called every frame
void ABaseCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LeftDoorTimeline != NULL)																							//Allowing the timeline events to tick so that they can be called on each frame
	{
		LeftDoorTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}

	if (RightDoorTimeline != NULL)
	{
		RightDoorTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}

	if (HoodTimeline != NULL)
	{
		HoodTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}

	if (TrunkTimeline != NULL)
	{
		TrunkTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}
}

void ABaseCar::ControlLeftDoor()
{
	CurveFloatValue = DoorCurve->GetFloatValue(LeftDoorTimeline->GetPlaybackPosition());								//Get the current position's float value from the timeline
	LeftDoorMesh->SetRelativeRotation(SwitchAxis(Door1Rotation.GetValue()));
}

void ABaseCar::SetLeftDoorState()																						//Function gets called after the timeline is finished executing completely
{
	CanRotateLeftDoor = true;
}

void ABaseCar::ControlRightDoor()																						//Get The Current position float value from the timeline
{
	//Get the current position's float value from the timeline
	CurveFloatValue = DoorCurve->GetFloatValue(RightDoorTimeline->GetPlaybackPosition());
	RightDoorMesh->SetRelativeRotation(SwitchAxis(Door2Rotation.GetValue()));
}

void ABaseCar::SetRightDoorState()																						//Function gets called after the LeftDoorTimeline is finished executing completely
{
	CanRotateRightDoor = true;
}

void ABaseCar::ControlHood()
{
	//Get the current position's float value from the timeline
	CurveFloatValue = HoodCurve->GetFloatValue(HoodTimeline->GetPlaybackPosition());
	HoodMesh->SetRelativeRotation(SwitchAxis(HoodRotation.GetValue()));
}

void ABaseCar::SetHoodState()
{
	CanRotateHood = true;
}

void ABaseCar::ControlTrunk()
{
	//Get the current position's float value from the timeline
	CurveFloatValue = TrunkCurve->GetFloatValue(TrunkTimeline->GetPlaybackPosition());
	TrunkMesh->SetRelativeRotation(SwitchAxis(TrunkRotation.GetValue()));
}

void ABaseCar::SetTrunkState()
{
	CanRotateTrunk = true;
}

FQuat ABaseCar::SwitchAxis(int MyAxis)
{
	FQuat NewRotation;
	switch (MyAxis)																						//Settting the rotation value to the axis in which the mesh is to rotate
	{
	case 0: NewRotation = FQuat(FRotator(CurveFloatValue, 0.0f, 0.0f));
			break;
	case 1: NewRotation = FQuat(FRotator(0.0f, CurveFloatValue, 0.0f));
			break;
	case 2: NewRotation = FQuat(FRotator(0.0f, 0.0f, CurveFloatValue));
			break;

	default:NewRotation = FQuat(FRotator(CurveFloatValue, 0.0f, 0.0f));
			break;
	}
	return NewRotation;
}

void ABaseCar::ToogleLeftDoor()
{
	if (CanRotateLeftDoor && (LeftDoorTimeline != NULL))																//Check to see if the door is currently rotating and do we have the Timeline
	{
		if (!IsLeftDoorOpen)
		{
			IsLeftDoorOpen = true;
			LeftDoorTimeline->PlayFromStart();
		}
		else
		{
			IsLeftDoorOpen = false;
			LeftDoorTimeline->Reverse();
		}
	}
}

void ABaseCar::ToogleRightDoor()
{
	if (CanRotateRightDoor && (RightDoorTimeline != NULL))																//Check to see if the door is currently rotating and do we have the Timeline
	{
		if (!IsRightDoorOpen)
		{
			IsRightDoorOpen = true;
			RightDoorTimeline->PlayFromStart();
		}
		else
		{
			IsRightDoorOpen = false;
			RightDoorTimeline->Reverse();
		}
	}
}

void ABaseCar::ToggleHood()
{
	if (CanRotateHood && (HoodTimeline != NULL))															//Check to see if the Hood is currently rotating and do we have the Timeline
	{
		if (!IsHoodOpen)
		{
			IsHoodOpen = true;
			HoodTimeline->PlayFromStart();
		}
		else
		{
			IsHoodOpen = false;
			HoodTimeline->Reverse();
		}
	}
}

void ABaseCar::ToggleTrunk()
{
	if (CanRotateTrunk && (TrunkTimeline != NULL))															//Check to see if the Trunk is currently rotating and do we have the Timeline
	{
		if (!IsTrunkOpen)
		{
			IsTrunkOpen = true;
			TrunkTimeline->PlayFromStart();
		}
		else
		{
			IsTrunkOpen = false;
			TrunkTimeline->Reverse();
		}
	}
}


