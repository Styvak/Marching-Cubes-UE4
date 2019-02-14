// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IBlock.h"

/**
 * 
 */
class MARCHINGCUBES_API ABlock : public IBlock
{
public:
	virtual int8 IsSolid() const override;
};
