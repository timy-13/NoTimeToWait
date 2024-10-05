// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NoTimeToWaitPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NOTIMETOWAIT_API ANoTimeToWaitPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void SetPlayerEnabledState(bool bPlayerEnabled);
};
