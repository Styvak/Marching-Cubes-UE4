// Fill out your copyright notice in the Description page of Project Settings.

#include "BIPlain.h"

#include "IBlock.h"
#include "BlockManager.h"

BIPlain::BIPlain(int Seed) : ABiome(Seed), noise(Seed), caveNoise(Seed)
{
	noise.SetNoiseType(FastNoise::Simplex);
	noise.SetFractalType(FastNoise::FBM);
	noise.SetFractalOctaves(7);
	noise.SetFrequency(0.0002f);

	caveNoise.SetNoiseType(FastNoise::PerlinFractal);
	caveNoise.SetFractalType(FastNoise::Billow);
	caveNoise.SetFractalOctaves(1);
	caveNoise.SetFrequency(0.0003f);
	caveNoise.SetFractalLacunarity(1);
	caveNoise.SetFractalGain(0.8);
	caveNoise.SetInterp(FastNoise::Quintic);
}

BIPlain::~BIPlain()
{
}

void BIPlain::FillColumn(const FVector &pos, const IBlock **Column, unsigned int BaseHeight, uint16 HeightDivision, unsigned int MaxHeight, uint16 HeightSize) const
{
	float height = noise.GetNoise(pos.X, pos.Y);
	float heightScale = (float)HeightSize / (float)HeightDivision;
	unsigned int heightDivision = MaxHeight * 0.6f;

	heightDivision += (unsigned int)((height + 1.f) / 2.f * (MaxHeight * 0.2f));
	for (unsigned int z = BaseHeight; z < BaseHeight + HeightDivision; z++) {
		if (z < MaxHeight * 0.56f && caveNoise.GetNoise(pos.X, z * heightScale, pos.Y) < -0.65f) {
			Column[z - BaseHeight] = BlockManager::GetInstance()->GetBlock(BlockID::AIR);
		}
		else if (z < heightDivision - 5) {
			Column[z - BaseHeight] = BlockManager::GetInstance()->GetBlock(BlockID::STONE);
		}
		else if (z < heightDivision) {
			Column[z - BaseHeight] = BlockManager::GetInstance()->GetBlock(BlockID::DIRT);
		}
		else if (z == heightDivision) {
			Column[z - BaseHeight] = BlockManager::GetInstance()->GetBlock(BlockID::GRASS);
		}
		else {
			Column[z - BaseHeight] = BlockManager::GetInstance()->GetBlock(BlockID::AIR);
		}
	}
}