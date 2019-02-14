// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ABlock.h"

/**
 * 
 */
class MARCHINGCUBES_API BStone : public ABlock
{
public:
	BStone();
	virtual ~BStone();

	virtual FLinearColor GetVertexColor() const override;
};
