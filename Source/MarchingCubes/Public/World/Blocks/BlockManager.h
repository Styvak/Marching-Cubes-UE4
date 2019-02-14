// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class IBlock;
enum class BlockID : uint8;

/**
 * 
 */
class MARCHINGCUBES_API BlockManager
{
public:
	BlockManager();
	~BlockManager();

	void RegisterBlocks();

	const IBlock *GetBlock(BlockID id) const;

	static BlockManager *GetInstance();

private:
	TArray<IBlock *> Blocks;

	static BlockManager *Instance;
};
