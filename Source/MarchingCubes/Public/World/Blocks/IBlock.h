// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class BlockID : uint8 {
	AIR = 0,
	STONE = 1,
	GRASS = 2,
	DIRT = 3,
	END
};

/**
 * 
 */
class MARCHINGCUBES_API IBlock
{
public:
	virtual ~IBlock() {}

	virtual int8 IsSolid() const = 0;
	virtual FLinearColor GetVertexColor() const = 0;
};
