// Fill out your copyright notice in the Description page of Project Settings.

#include "SDTAIController.h"
#include "SoftDesignTraining.h"

void ASDTAIController::Tick(float deltaTime)
{
    Move(FVector2D(1,1),1.0,25,deltaTime);
}


void ASDTAIController::Move(const FVector2D& direction, float acceleration, float maxSpeed, float deltaTime)
{
	APawn* pawn = GetPawn();
	m_currentSpeed = FMath::Min(maxSpeed, m_currentSpeed + acceleration * deltaTime);
	FVector const forwardDirection = GetPawn()->GetActorForwardVector();

	float AimAtAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(forwardDirection, FVector(direction, 0.f).GetSafeNormal())));
	FVector crossProduct = FVector::CrossProduct(forwardDirection, FVector(direction, 0.f).GetSafeNormal()).GetSafeNormal();
	if (crossProduct.Z == -1.0f)
		AimAtAngle = -AimAtAngle;

	//FRotator NewRotation = FRotator(0, AimAtAngle, 0);
	pawn->AddMovementInput(FVector(direction, 0.f), m_currentSpeed);
	//pawn->AddActorWorldRotation(NewRotation);

	pawn->SetActorRotation(FMath::Lerp(pawn->GetActorRotation(), FVector(direction, 0.f).Rotation(), 0.1f));
}