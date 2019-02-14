// Fill out your copyright notice in the Description page of Project Settings.

#include "BlockManager.h"

#include "BAir.h"
#include "BStone.h"
#include "BDirt.h"
#include "BGrass.h"

BlockManager *BlockManager::Instance = nullptr;

BlockManager::BlockManager()
{
	RegisterBlocks();
}

BlockManager::~BlockManager()
{
}

void BlockManager::RegisterBlocks()
{
	Blocks.SetNum(static_cast<uint8>(BlockID::END));

	Blocks[static_cast<uint8>(BlockID::AIR)] = new BAir;
	Blocks[static_cast<uint8>(BlockID::STONE)] = new BStone;
	Blocks[static_cast<uint8>(BlockID::GRASS)] = new BGrass;
	Blocks[static_cast<uint8>(BlockID::DIRT)] = new BDirt;
}

const IBlock *BlockManager::GetBlock(BlockID id) const
{
	return Blocks[static_cast<uint8>(id)];
}

BlockManager *BlockManager::GetInstance()
{
	if (!Instance)
		Instance = new BlockManager;
	return Instance;
}