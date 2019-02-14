// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ABiome.h"
#include "FastNoise.h"

/**
 * 
 */
class MARCHINGCUBES_API BIPlain : public ABiome
{
public:
	BIPlain(int Seed);
	~BIPlain();

	virtual void FillColumn(const FVector &pos, const IBlock **Column, unsigned int BaseHeight, uint16 HeightDivision, unsigned int MaxHeight, uint16 HeightSize) const override;

private:
	FastNoise noise;
	FastNoise caveNoise;
};
