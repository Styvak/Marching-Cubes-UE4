// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class IBiome;
class IBlock;

/**
 * 
 */
class MARCHINGCUBES_API BiomeGenerator
{
public:
	BiomeGenerator(int Seed);
	~BiomeGenerator();

	void FillColumn(const FVector &pos, const IBlock **column, unsigned int BaseHeight, uint16 HeightDivision, unsigned int MaxHeight, uint16 HeightSize) const;

private:
	int Seed;
	IBiome *CurrentBiome;
};
