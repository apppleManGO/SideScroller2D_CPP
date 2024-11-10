// Copyright Epic Games, Inc. All Rights Reserved.

#include "SideScroller2D_CPPGameMode.h"
#include "SideScroller2D_CPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASideScroller2D_CPPGameMode::ASideScroller2D_CPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
