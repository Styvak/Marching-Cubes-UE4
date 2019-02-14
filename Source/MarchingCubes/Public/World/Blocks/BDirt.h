// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ABlock.h"

/**
 * 
 */
class MARCHINGCUBES_API BDirt : public ABlock
{
public:
	BDirt();
	virtual ~BDirt();

	virtual FLinearColor GetVertexColor() const override;
};
