// Copyright by David Backes

/*
	Camera and Movement Controlling
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MRC_PlayerPawn.generated.h"


class USceneComponent;
class USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class MERCORYN_API AMRC_PlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMRC_PlayerPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UFloatingPawnMovement* FloatingPawnMovement;

	// Movement
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Controller")
	float MovementSpeed = 1.0f;

	// Camera zoom
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Controller")
	float CameraDistance = 500.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Controller")
	float CameraZoomSensitivity = 500.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Controller")
	float CameraZoomSpeed = 10.0f;

	// Rotation
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Controller")
	float RotationSensitivity = 0.5f;

	// Scroll
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Controller")
	float EdgeScrollSpeed = 1.5f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Controller")
	float EdgeDistanceFrac = 0.1f;


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MovementAction;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Input")
	UInputAction* ZoomAction;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Input")
	UInputAction* RotateHoldAction;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Input")
	UInputAction* RotateAction;


private:
	float CameraDistanceTarget;
	float CameraAngle;
	bool bIsRotating;
	float MouseX;
	float MouseY;
	FVector2D ViewportSize;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	void Move(const FInputActionValue& Value);
	void Zoom(const FInputActionValue& Value);
	void RotateStart();
	void RotateEnd();
	void Rotate(const FInputActionValue& Value);

	void CalculateCameraTransform(float DeltaTime);
	void EdgeScroll();

};
