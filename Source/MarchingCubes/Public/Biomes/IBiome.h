// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class IBlock;

/**
 * 
 */
class MARCHINGCUBES_API IBiome
{
public:
	virtual ~IBiome() {}

	virtual void FillColumn(const FVector &pos, const IBlock **Column, unsigned int BaseHeight, uint16 HeightDivision, unsigned int MaxHeight, uint16 HeightSize) const = 0;
};
