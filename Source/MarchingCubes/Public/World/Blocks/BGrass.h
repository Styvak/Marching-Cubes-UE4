// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ABlock.h"

/**
 * 
 */
class MARCHINGCUBES_API BGrass : public ABlock
{
public:
	BGrass();
	virtual ~BGrass();

	virtual FLinearColor GetVertexColor() const override;
};
