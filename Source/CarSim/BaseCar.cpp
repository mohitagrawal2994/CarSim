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

	bReplicates = true;

	BaseCarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseCarMesh"));				//Creating/Assigning MeshComponent to the mesh pointers
	RootComponent = BaseCarMesh;
	BaseCarMesh->SetMobility(EComponentMobility::Static);
	//Door & Window Meshes
	LeftFrontDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftFrontDoorMesh"));
	LeftFrontDoorMesh->SetupAttachment(RootComponent);
	LeftFrontDoorMesh->SetMobility(EComponentMobility::Movable);

	LeftFrontWindowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftFrontWindowMesh"));
	LeftFrontWindowMesh->SetupAttachment(LeftFrontDoorMesh);
	LeftFrontWindowMesh->SetMobility(EComponentMobility::Movable);

	LeftBackDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftBackDoorMesh"));
	LeftBackDoorMesh->SetupAttachment(RootComponent);
	LeftBackDoorMesh->SetMobility(EComponentMobility::Movable);

	LeftBackWindowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftBackWindowMesh"));
	LeftBackWindowMesh->SetupAttachment(LeftBackDoorMesh);
	LeftBackWindowMesh->SetMobility(EComponentMobility::Movable);

	RightFrontDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightFrontDoorMesh"));
	RightFrontDoorMesh->SetupAttachment(RootComponent);
	RightFrontDoorMesh->SetMobility(EComponentMobility::Movable);

	RightFrontWindowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightFrontWindowMesh"));
	RightFrontWindowMesh->SetupAttachment(RightFrontDoorMesh);
	RightFrontWindowMesh->SetMobility(EComponentMobility::Movable);

	RightBackDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightBackDoorMesh"));
	RightBackDoorMesh->SetupAttachment(RootComponent);
	RightBackDoorMesh->SetMobility(EComponentMobility::Movable);

	RightBackWindowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightBackWindowMesh"));
	RightBackWindowMesh->SetupAttachment(RightBackDoorMesh);
	RightBackWindowMesh->SetMobility(EComponentMobility::Movable);

	//Hood & Trunk Meshes
	TrunkMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrunkMesh"));
	TrunkMesh->SetupAttachment(RootComponent);
	TrunkMesh->SetMobility(EComponentMobility::Movable);

	HoodMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HoodMesh"));
	HoodMesh->SetupAttachment(RootComponent);
	HoodMesh->SetMobility(EComponentMobility::Movable);

	LeftFrontDoorOBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LFDoorOverlapBox"));			//Assigning a static box component
	LeftFrontDoorOBox->SetupAttachment(LeftFrontDoorMesh);
	LeftFrontDoorOBox->SetMobility(EComponentMobility::Movable);

	LeftBackDoorOBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LBDoorOverlapBox"));			//Assigning a static box component
	LeftBackDoorOBox->SetupAttachment(LeftBackDoorMesh);
	LeftBackDoorOBox->SetMobility(EComponentMobility::Movable);

	RightFrontDoorOBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RFDoorOverlapBox"));		//Assigning a static box component
	RightFrontDoorOBox->SetupAttachment(RightFrontDoorMesh);
	RightFrontDoorOBox->SetMobility(EComponentMobility::Movable);

	RightBackDoorOBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RBDoorOverlapBox"));		//Assigning a static box component
	RightBackDoorOBox->SetupAttachment(RightBackDoorMesh);
	RightBackDoorOBox->SetMobility(EComponentMobility::Movable);

	HoodOBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HoodOverlapBox"));			//Assigning a static box component
	HoodOBox->SetupAttachment(RootComponent);
	HoodOBox->SetMobility(EComponentMobility::Movable);

	TrunkOBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TrunkOverlapBox"));		//Assigning a static box component
	TrunkOBox->SetupAttachment(RootComponent);
	TrunkOBox->SetMobility(EComponentMobility::Movable);

	SteeringMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SteeringMesh"));
	SteeringMesh->SetupAttachment(RootComponent);
	SteeringMesh->SetMobility(EComponentMobility::Movable);

	SteeringOBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SteeringOverlapBox"));		//Assigning a static box component
	SteeringOBox->SetupAttachment(SteeringMesh);
	SteeringOBox->SetMobility(EComponentMobility::Movable);

	GearMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GearMesh"));
	GearMesh->SetupAttachment(RootComponent);
	GearMesh->SetMobility(EComponentMobility::Movable);

	//Wheel & Their Rims Meshes
	LeftFrontWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftFrontWheel"));
	LeftFrontWheel->SetupAttachment(RootComponent);
	LeftFrontWheel->SetMobility(EComponentMobility::Movable);

	LeftBackWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftBackWheel"));
	LeftBackWheel->SetupAttachment(RootComponent);
	LeftBackWheel->SetMobility(EComponentMobility::Movable);

	RightFrontWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightFrontWheel"));
	RightFrontWheel->SetupAttachment(RootComponent);
	RightFrontWheel->SetMobility(EComponentMobility::Movable);

	RightBackWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightBackWheel"));
	RightBackWheel->SetupAttachment(RootComponent);
	RightBackWheel->SetMobility(EComponentMobility::Movable);

	LeftFrontWheelRim = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftFrontWheelRim"));
	LeftFrontWheelRim->SetupAttachment(LeftFrontWheel);
	LeftFrontWheelRim->SetMobility(EComponentMobility::Movable);

	LeftBackWheelRim = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftBackWheelRim"));
	LeftBackWheelRim->SetupAttachment(LeftBackWheel);
	LeftBackWheelRim->SetMobility(EComponentMobility::Movable);

	RightFrontWheelRim = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightFrontWheelRim"));
	RightFrontWheelRim->SetupAttachment(RightFrontWheel);
	RightFrontWheelRim->SetMobility(EComponentMobility::Movable);

	RightBackWheelRim = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightBackWheelRim"));
	RightBackWheelRim->SetupAttachment(RightBackWheel);
	RightBackWheelRim->SetMobility(EComponentMobility::Movable);

	HoodIsFlipped = false;
	Has4Doors = false;

	CanRotateLeftFrontDoor = true;													//Variables to check of the mesh can be rotated i.e. avoids interfering with the mesh if it is being rotated
	CanRotateLeftFrontWindow = true;
	CanRotateLeftBackDoor = true;
	CanRotateLeftBackWindow = true;
	CanRotateRightFrontDoor = true;
	CanRotateRightFrontWindow = true;
	CanRotateRightBackDoor = true;
	CanRotateRightBackWindow = true;
	CanRotateHood = true;
	CanRotateTrunk = true;

	IsLeftFrontDoorOpen = false;												//Variables to check if the car parts are in opened state
	IsLeftFrontWindowOpen = false;
	IsLeftBackDoorOpen = false;
	IsLeftBackWindowOpen = false;
	IsRightFrontDoorOpen = false;
	IsRightFrontWindowOpen = false;
	IsRightBackDoorOpen = false;
	IsRightBackWindowOpen = false;
	IsHoodOpen = false;
	IsTrunkOpen = false;

	CurveFloatValue = 0;

	LeftFrontDoorTimeline = NULL;											//Setting Timelines to NULL
	LeftFrontWindowTimeline = NULL;
	LeftBackDoorTimeline = NULL;
	LeftBackWindowTimeline = NULL;
	RightFrontDoorTimeline = NULL;
	RightFrontWindowTimeline = NULL;
	RightBackDoorTimeline = NULL;
	RightBackWindowTimeline = NULL;
	HoodTimeline = NULL;
	TrunkTimeline = NULL;
}
// Called when the game starts or when spawned
void ABaseCar::BeginPlay()
{
	Super::BeginPlay();

	if (DoorCurve)															//Checking if the curves exist then binding functions to it
	{
		FrontDoorBindFunc();												//Calling function to bind the front doors timeline
		if (Has4Doors)														//Do if Car has 4 Doors
		{																					//Binding The Back Door Functions
			FOnTimelineFloat LeftBackDoorCallback;
			FOnTimelineEventStatic LeftBackDoorFinishedCallback;

			FOnTimelineFloat RightBackDoorCallback;
			FOnTimelineEventStatic RightBackDoorFinishedCallback;

			LeftBackDoorCallback.BindUFunction(this, FName("ControlLeftBackDoor"));
			LeftBackDoorFinishedCallback.BindUFunction(this, FName("SetLeftBackDoorState"));

			RightBackDoorCallback.BindUFunction(this, FName("ControlRightBackDoor"));
			RightBackDoorFinishedCallback.BindUFunction(this, FName("SetRightBackDoorState"));

			LeftBackDoorTimeline = NewObject<UTimelineComponent>(this, FName("LeftBackDoorAnimation"));
			LeftBackDoorTimeline->AddInterpFloat(DoorCurve, LeftBackDoorCallback);
			LeftBackDoorTimeline->SetTimelineFinishedFunc(LeftBackDoorFinishedCallback);
			LeftBackDoorTimeline->RegisterComponent();

			RightBackDoorTimeline = NewObject<UTimelineComponent>(this, FName("RightBackDoorAnimation"));
			RightBackDoorTimeline->AddInterpFloat(DoorCurve, RightBackDoorCallback);
			RightBackDoorTimeline->SetTimelineFinishedFunc(RightBackDoorFinishedCallback);
			RightBackDoorTimeline->RegisterComponent();
		}
		else
		{
			//Destroy static meshes
			//Delete Timeline
			LeftBackDoorMesh->DestroyComponent();
			RightBackDoorMesh->DestroyComponent();
			LeftBackDoorTimeline = NULL;
			RightBackDoorTimeline = NULL;
		}
	}
	if ((WindowXCurve != NULL) && (WindowZCurve != NULL))
	{
		FrontWindowBindFunc();
		if (Has4Doors)
		{

		}
		else
		{
			LeftBackWindowMesh->DestroyComponent();
			RightBackWindowMesh->DestroyComponent();
			LeftBackWindowTimeline = NULL;
			RightBackWindowTimeline = NULL;
		}
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

	if (Has4Doors)
	{
		if (LeftBackDoorTimeline != NULL)																							//Allowing the timeline events to tick so that they can be called on each frame
		{
			LeftBackDoorTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
		}

		if (RightBackDoorTimeline != NULL)
		{
			RightBackDoorTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
		}
	}

	if (LeftFrontDoorTimeline != NULL)																							//Allowing the timeline events to tick so that they can be called on each frame
	{
		LeftFrontDoorTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}

	if (RightFrontDoorTimeline != NULL)
	{
		RightFrontDoorTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
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

void ABaseCar::FrontDoorBindFunc()
{
	FOnTimelineFloat LeftFrontDoorCallback;
	FOnTimelineEventStatic LeftFrontDoorFinishedCallback;

	FOnTimelineFloat RightFrontDoorCallback;
	FOnTimelineEventStatic RightFrontDoorFinishedCallback;

	LeftFrontDoorCallback.BindUFunction(this, FName("ControlLeftFrontDoor"));
	LeftFrontDoorFinishedCallback.BindUFunction(this, FName("SetLeftFrontDoorState"));

	RightFrontDoorCallback.BindUFunction(this, FName("ControlRightFrontDoor"));
	RightFrontDoorFinishedCallback.BindUFunction(this, FName("SetRightFrontDoorState"));

	LeftFrontDoorTimeline = NewObject<UTimelineComponent>(this, FName("LeftFrontDoorAnimation"));
	LeftFrontDoorTimeline->AddInterpFloat(DoorCurve, LeftFrontDoorCallback);
	LeftFrontDoorTimeline->SetTimelineFinishedFunc(LeftFrontDoorFinishedCallback);
	LeftFrontDoorTimeline->RegisterComponent();

	RightFrontDoorTimeline = NewObject<UTimelineComponent>(this, FName("RightFrontDoorAnimation"));
	RightFrontDoorTimeline->AddInterpFloat(DoorCurve, RightFrontDoorCallback);
	RightFrontDoorTimeline->SetTimelineFinishedFunc(RightFrontDoorFinishedCallback);
	RightFrontDoorTimeline->RegisterComponent();
}

void ABaseCar::FrontWindowBindFunc()
{
}

//MOVING THE LEFT DOORS
void ABaseCar::ControlLeftFrontDoor()
{
	CurveFloatValue = DoorCurve->GetFloatValue(LeftFrontDoorTimeline->GetPlaybackPosition());								//Get the current position's float value from the timeline
	LeftFrontDoorMesh->SetRelativeRotation(SwitchAxis(LeftFrontDoorRotation.GetValue()));
}

void ABaseCar::SetLeftFrontDoorState()																						//Function gets called after the timeline is finished executing completely
{
	CanRotateLeftFrontDoor = true;
}

void ABaseCar::ControlLeftBackDoor()
{
	CurveFloatValue = DoorCurve->GetFloatValue(LeftBackDoorTimeline->GetPlaybackPosition());								//Get the current position's float value from the timeline
	LeftBackDoorMesh->SetRelativeRotation(SwitchAxis(LeftBackDoorRotation.GetValue()));
}

void ABaseCar::SetLeftBackDoorState()																						//Function gets called after the timeline is finished executing completely
{
	CanRotateLeftBackDoor = true;
}

//MOVING THE RIGHT DOOR
void ABaseCar::ControlRightFrontDoor()																						//Get The Current position float value from the timeline
{
	//Get the current position's float value from the timeline
	CurveFloatValue = DoorCurve->GetFloatValue(RightFrontDoorTimeline->GetPlaybackPosition());
	RightFrontDoorMesh->SetRelativeRotation(SwitchAxis(RightFrontDoorRotation.GetValue()));
}

void ABaseCar::SetRightFrontDoorState()																						//Function gets called after the LeftDoorTimeline is finished executing completely
{
	CanRotateRightFrontDoor = true;
}

void ABaseCar::ControlRightBackDoor()																						//Get The Current position float value from the timeline
{
	//Get the current position's float value from the timeline
	CurveFloatValue = DoorCurve->GetFloatValue(RightBackDoorTimeline->GetPlaybackPosition());
	RightBackDoorMesh->SetRelativeRotation(SwitchAxis(RightBackDoorRotation.GetValue()));
}

void ABaseCar::SetRightBackDoorState()																						//Function gets called after the LeftDoorTimeline is finished executing completely
{
	CanRotateRightBackDoor = true;
}

//MOVING HOOD & TRUNK
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
	case 1:	NewRotation = FQuat(FRotator(-CurveFloatValue, 0.0f, 0.0f));
		break;
	case 2: NewRotation = FQuat(FRotator(0.0f, CurveFloatValue, 0.0f));
		break;
	case 3: NewRotation = FQuat(FRotator(0.0f, -CurveFloatValue, 0.0f));
		break;
	case 4: NewRotation = FQuat(FRotator(0.0f, 0.0f, CurveFloatValue));
		break;
	case 5: NewRotation = FQuat(FRotator(0.0f, 0.0f, -CurveFloatValue));
		break;

	default:NewRotation = FQuat(FRotator(CurveFloatValue, 0.0f, 0.0f));
		break;
	}
	return NewRotation;
}

//CONTROL THE LEFT DOORS OPENING/CLOSING
void ABaseCar::ToggleLeftFrontDoor()
{
	if (CanRotateLeftFrontDoor && (LeftFrontDoorTimeline != NULL))																//Check to see if the door is currently rotating and do we have the Timeline
	{
		if (!IsLeftFrontDoorOpen)
		{
			IsLeftFrontDoorOpen = true;
			LeftFrontDoorTimeline->PlayFromStart();
		}
		else
		{
			IsLeftFrontDoorOpen = false;
			LeftFrontDoorTimeline->Reverse();
		}
	}
}

void ABaseCar::ToggleLeftBackDoor()
{
	if (CanRotateLeftBackDoor && (LeftBackDoorTimeline != NULL))																//Check to see if the door is currently rotating and do we have the Timeline
	{
		if (!IsLeftBackDoorOpen)
		{
			IsLeftBackDoorOpen = true;
			LeftBackDoorTimeline->PlayFromStart();
		}
		else
		{
			IsLeftBackDoorOpen = false;
			LeftBackDoorTimeline->Reverse();
		}
	}
}

//CONTROL THE RIGHT DOORS OPENING/CLOSING
void ABaseCar::ToggleRightFrontDoor()
{
	if (CanRotateRightFrontDoor && (RightFrontDoorTimeline != NULL))																//Check to see if the door is currently rotating and do we have the Timeline
	{
		if (!IsRightFrontDoorOpen)
		{
			IsRightFrontDoorOpen = true;
			RightFrontDoorTimeline->PlayFromStart();
		}
		else
		{
			IsRightFrontDoorOpen = false;
			RightFrontDoorTimeline->Reverse();
		}
	}
}

void ABaseCar::ToggleRightBackDoor()
{
	if (CanRotateRightBackDoor && (RightBackDoorTimeline != NULL))																//Check to see if the door is currently rotating and do we have the Timeline
	{
		if (!IsRightBackDoorOpen)
		{
			IsRightBackDoorOpen = true;
			RightBackDoorTimeline->PlayFromStart();
		}
		else
		{
			IsRightBackDoorOpen = false;
			RightBackDoorTimeline->Reverse();
		}
	}
}

//CONTROL THE HOOD & TRUNK OPENING/CLOSING
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