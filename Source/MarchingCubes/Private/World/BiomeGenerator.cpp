// Fill out your copyright notice in the Description page of Project Settings.

#include "BiomeGenerator.h"

#include "BIPlain.h"

BiomeGenerator::BiomeGenerator(int Seed) : Seed(Seed), CurrentBiome(new BIPlain(Seed))
{
}

BiomeGenerator::~BiomeGenerator()
{
}

void BiomeGenerator::FillColumn(const FVector &pos, const IBlock **column, unsigned int BaseHeight, uint16 HeightDivision, unsigned int MaxHeight, uint16 HeightSize) const
{
	CurrentBiome->FillColumn(pos, column, BaseHeight, HeightDivision, MaxHeight, HeightSize);
}