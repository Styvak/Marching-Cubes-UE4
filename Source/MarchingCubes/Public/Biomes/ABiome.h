// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IBiome.h"

/**
 * 
 */
class MARCHINGCUBES_API ABiome : public IBiome
{
public:
	ABiome(int Seed);
	virtual ~ABiome();

protected:
	int Seed;

private:
};
