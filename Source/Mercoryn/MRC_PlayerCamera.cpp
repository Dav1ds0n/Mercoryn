// Copyright by David Backes

#include "MRC_PlayerCamera.h"

#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
AMRC_PlayerCamera::AMRC_PlayerCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>("Scene Root");
	SetRootComponent(SceneRoot);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	CameraBoom->SetupAttachment(SceneRoot);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 25.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CameraBoom);
	Camera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f), false, nullptr, ETeleportType::None);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("Floating Pawn Movement");


}

// Called when the game starts or when spawned
void AMRC_PlayerCamera::BeginPlay()
{
	Super::BeginPlay();
	
	CameraDistanceTarget = CameraDistance;
	CalculateCameraTransform(0.0f);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetShowMouseCursor(true);
}

// Called every frame
void AMRC_PlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalculateCameraTransform(DeltaTime);

	//EdgeScroll();
}

// Called to bind functionality to input
void AMRC_PlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AMRC_PlayerCamera::Move);
	Input->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AMRC_PlayerCamera::Zoom);
	Input->BindAction(RotateHoldAction, ETriggerEvent::Triggered, this, &AMRC_PlayerCamera::RotateStart);
	Input->BindAction(RotateHoldAction, ETriggerEvent::Completed, this, &AMRC_PlayerCamera::RotateEnd);
	Input->BindAction(RotateAction, ETriggerEvent::Triggered, this, &AMRC_PlayerCamera::Rotate);


}

void AMRC_PlayerCamera::Move(const FInputActionValue& Value)
{
	FVector2D MovementInput = Value.Get<FVector2D>();
	FVector Movement = GetActorForwardVector() * MovementInput.Y + GetActorRightVector() * MovementInput.X;

	FloatingPawnMovement->AddInputVector(Movement * MovementSpeed, false);
}

void AMRC_PlayerCamera::Zoom(const FInputActionValue& Value)
{
	CameraDistanceTarget = FMath::Clamp(CameraDistance - (Value.Get<float>() * CameraZoomSensitivity), 500.0f, 5000.0f);
}

void AMRC_PlayerCamera::RotateStart()
{
	if (bIsRotating) {
		return;
	}
	bIsRotating = true;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetShowMouseCursor(false);
	PlayerController->GetMousePosition(MouseX, MouseY);

	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(false);

	PlayerController->SetInputMode(InputMode);

}

void AMRC_PlayerCamera::RotateEnd()
{
	if (!bIsRotating) {
		return;
	}
	bIsRotating = false;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetShowMouseCursor(true);
	PlayerController->SetMouseLocation((int)MouseX, (int)MouseY);

	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetWidgetToFocus(nullptr);

	PlayerController->SetInputMode(InputMode);
}

void AMRC_PlayerCamera::Rotate(const FInputActionValue& Value)
{
	if (!bIsRotating) {
		return;
	}

	AddControllerYawInput(Value.Get<float>() * RotationSensitivity);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);	
	PlayerController->SetMouseLocation((int)MouseX, (int)MouseY);
}

void AMRC_PlayerCamera::CalculateCameraTransform(float DeltaTime)
{
	CameraDistance = FMath::FInterpTo(CameraDistance, CameraDistanceTarget, DeltaTime, CameraZoomSpeed);
	CameraAngle = FMath::Lerp(15.0f, 45.0f, CameraDistance / 5000.0f);

	CameraBoom->TargetArmLength = CameraDistance * FMath::Cos(FMath::DegreesToRadians(CameraAngle));
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, CameraDistance * FMath::Sin(FMath::DegreesToRadians(CameraAngle)));

	Camera->SetRelativeRotation(FRotator(CameraAngle * -1.0f, 0.0f, 0.0f), false, nullptr, ETeleportType::None);
}

void AMRC_PlayerCamera::EdgeScroll()
{
	ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->GetMousePosition(MouseX, MouseY);

	FVector2D MovementInput = FVector2D(0.0f, 0.0f);

	if (MouseX / ViewportSize.X > 1.0f - EdgeDistanceFrac) {
		MovementInput.X += 1.0f;
	}
	if (MouseX / ViewportSize.X < EdgeDistanceFrac) {
		MovementInput.X -= 1.0f;
	}
	if (MouseY / ViewportSize.Y > 1.0f - EdgeDistanceFrac) {
		MovementInput.Y -= 1.0f;
	}
	if (MouseY / ViewportSize.Y < EdgeDistanceFrac) {
		MovementInput.Y += 1.0f;
	}

	FVector Movement = GetActorForwardVector() * MovementInput.Y + GetActorRightVector() * MovementInput.X;
	FloatingPawnMovement->AddInputVector(Movement * EdgeScrollSpeed, false);

}

