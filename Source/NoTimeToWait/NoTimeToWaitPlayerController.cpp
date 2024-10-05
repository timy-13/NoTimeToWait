// Fill out your copyright notice in the Description page of Project Settings.


#include "NoTimeToWaitPlayerController.h"

#include "GameFramework/Pawn.h"

void ANoTimeToWaitPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    if (bPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }
    bShowMouseCursor = bPlayerEnabled;
}