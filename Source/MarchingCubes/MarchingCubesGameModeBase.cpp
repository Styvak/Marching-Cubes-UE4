// Fill out your copyright notice in the Description page of Project Settings.

#include "MarchingCubesGameModeBase.h"

#include "BlockManager.h"

void AMarchingCubesGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	BlockManager::GetInstance()->RegisterBlocks();
}