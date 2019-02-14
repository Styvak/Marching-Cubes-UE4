// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ABlock.h"

/**
 * 
 */
class MARCHINGCUBES_API BAir : public ABlock
{
public:
	BAir();
	virtual ~BAir();

	virtual int8 IsSolid() const override;
	virtual FLinearColor GetVertexColor() const override;
};
