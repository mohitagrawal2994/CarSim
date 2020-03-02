// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "MotionControllerComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "Net/UnrealNetwork.h"
#include "BaseCar.h"
#include "DrawDebugHelpers.h"
#include "EngineGlobals.h"

// Sets default values
AVRPawn::AVRPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	RootOffset = CreateDefaultSubobject<USceneComponent>(TEXT("RootOffset"));
	RootOffset->SetupAttachment(Root);
	RootOffset->SetMobility(EComponentMobility::Movable);

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(RootOffset);

	LeftHandMC = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftHandMotionController"));
	LeftHandMC->SetupAttachment(RootOffset);
	LeftHandMC->MotionSource = "Left";

	RightHandMC = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightHandMotionController"));
	RightHandMC->SetupAttachment(RootOffset);
	RightHandMC->MotionSource = "Right";

	LeftHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHandMesh"));
	LeftHandMesh->SetupAttachment(LeftHandMC);

	RightHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHandMesh"));
	RightHandMesh->SetupAttachment(RightHandMC);

	LeftHandOBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftHandOverlapBox"));
	LeftHandOBox->SetupAttachment(LeftHandMesh);
	LeftHandOBox->InitBoxExtent(FVector(8.0, 8.0, 8.0));

	RightHandOBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightHandOverlapBox"));
	RightHandOBox->SetupAttachment(RightHandMesh);
	RightHandOBox->InitBoxExtent(FVector(8.0, 8.0, 8.0));

	LeftHandOBox->OnComponentBeginOverlap.AddDynamic(this, &AVRPawn::OnOverlapBeginLeft);
	LeftHandOBox->OnComponentEndOverlap.AddDynamic(this, &AVRPawn::OnOverlapEndLeft);

	RightHandOBox->OnComponentBeginOverlap.AddDynamic(this, &AVRPawn::OnOverlapBeginRight);
	RightHandOBox->OnComponentEndOverlap.AddDynamic(this, &AVRPawn::OnOverlapEndRight);

	CanFindTeleportationPoint = false;
	ValidTeleportLocation = false;
	TeleportLocation = FVector::ZeroVector;

	LTraceStart = FVector::ZeroVector;
	LTraceEnd = FVector::ZeroVector;

	LeftHandState = 0.0;
	RightHandState = 0.0;
	LineTraceRange = 4000;

	MyCar = NULL;
	MyOverlappingComp = NULL;

}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
	GetCar();
	MyNavMesh = UNavigationSystemV1::GetCurrent(GetWorld());
}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CanFindTeleportationPoint)
	{
		LTraceStart = PlayerCamera->GetComponentLocation();
		LTraceEnd = LTraceStart + (LeftHandMC->GetForwardVector() * LineTraceRange);
		if (GetWorld()->LineTraceSingleByChannel(Hit, LTraceStart, LTraceEnd, ECC_Visibility))
		{
			if (Hit.bBlockingHit)
			{
				if (FVector::DotProduct(Hit.Normal, FVector(0.0, 0.0, 1.0)) > 0.9)
				{
					ValidTeleportLocation = true;
					if (MyNavMesh)
					{
						UE_LOG(LogTemp, Warning, TEXT("Found Navand Raytrace"));
						MyNavMesh->ProjectPointToNavigation(Hit.Location, ValTeleportLocation);
						DrawDebugCylinder(GetWorld(), FVector(ValTeleportLocation), (FVector(ValTeleportLocation) + Hit.Normal * 10), 50, 12, FColor(0, 181, 0), false, -1, 0, 0.5);
					}
				}
				else
				{
					ValidTeleportLocation = false;
				}
			}
		}
	}

}

void AVRPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate Current Car
	DOREPLIFETIME(AVRPawn, MyCar);
}

void AVRPawn::GetCar_Implementation()
{
	FoundCars.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCar::StaticClass(), FoundCars);

	if (FoundCars.Num() > 0)
	{
		MyCar = Cast<ABaseCar>(FoundCars[0]);
	}
}

bool AVRPawn::GetCar_Validate()
{
	return true;
}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Handles Teleportation Events
	PlayerInputComponent->BindAxis("TeleportXAxis", this, &AVRPawn::TeleportXAxis);
	PlayerInputComponent->BindAxis("TeleportYAxis", this, &AVRPawn::TeleportYAxis);
	PlayerInputComponent->BindAction("Teleport", IE_Pressed, this, &AVRPawn::CanFindTelPoint);
	PlayerInputComponent->BindAction("Teleport", IE_Released, this, &AVRPawn::TeleportTo);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AVRPawn::OnResetVR);

	// Handles Car Events
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AVRPawn::Action);

}

void AVRPawn::TeleportXAxis(float Value)
{
}

void AVRPawn::TeleportYAxis(float Value)
{
}

void AVRPawn::CanFindTelPoint()
{
	CanFindTeleportationPoint = true;
	UE_LOG(LogTemp, Warning, TEXT("Pressing to fid tel location"));
}

void AVRPawn::TeleportTo()
{
	UE_LOG(LogTemp, Warning, TEXT("Teleporting ti location"));
	if (CanFindTeleportationPoint && ValidTeleportLocation)
	{
		//Teleport to the new location
		TeleportLocation = FVector(FVector(ValTeleportLocation).X + PlayerCamera->GetRelativeLocation().X, FVector(ValTeleportLocation).Y + PlayerCamera->GetRelativeLocation().Y, FVector(ValTeleportLocation).Z);
		this->SetActorLocation(TeleportLocation);

		//Setting values to false once teleported
		CanFindTeleportationPoint = false;
		ValidTeleportLocation = false;
	}
}

void AVRPawn::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AVRPawn::Action()
{
	AllowToggleCarParts();

}
void AVRPawn::AllowToggleCarParts_Implementation()
{
	ToggleCarParts();
}

bool AVRPawn::AllowToggleCarParts_Validate()
{
	return true;
}

void AVRPawn::ToggleCarParts_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Triggering Action"));
	if ((MyCar != NULL) && (MyOverlappingComp != NULL))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Triggering Action with variables found"));
		if (MyOverlappingComp == MyCar->LeftFrontDoorOBox)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlapping LeftFrontDoorOBox"));
			MyCar->ToggleLeftFrontDoor();
		}
		else if (MyOverlappingComp == MyCar->LeftBackDoorOBox)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlapping LeftBackDoorOBox"));
			MyCar->ToggleLeftBackDoor();
		}
		else if (MyOverlappingComp == MyCar->RightFrontDoorOBox)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlapping RightFrontDoorOBox"));
			MyCar->ToggleRightFrontDoor();
		}
		else if (MyOverlappingComp == MyCar->RightBackDoorOBox)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlapping RightBackDoorOBox"));
			MyCar->ToggleRightBackDoor();
		}
		else if (MyOverlappingComp == MyCar->HoodOBox)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlapping HoodOBox"));
			MyCar->ToggleHood();
		}
		else if (MyOverlappingComp == MyCar->TrunkOBox)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlapping TrunkOBox"));
			MyCar->ToggleTrunk();
		}
		else
		{
			MyOverlappingComp = NULL;
		}
	}
}

bool AVRPawn::ToggleCarParts_Validate()
{
	return true;
}

float AVRPawn::GetLeftHandState()
{
	return LeftHandState;
}

float AVRPawn::GetRightHandState()
{
	return RightHandState;
}

void AVRPawn::OnOverlapBeginLeft(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, OtherComp->GetName());
	if (OtherActor->GetClass()->IsChildOf(ABaseCar::StaticClass()))
	{
		MyOverlappingComp = OtherComp;
	}
}

void AVRPawn::OnOverlapEndLeft(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("FinshedLeftOverlapping"));
}

void AVRPawn::OnOverlapBeginRight(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, OtherComp->GetName());
	if (OtherActor->GetClass()->IsChildOf(ABaseCar::StaticClass()))
	{
		MyOverlappingComp = OtherComp;
	}
}

void AVRPawn::OnOverlapEndRight(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("FinshedRightOverlapping"));
}