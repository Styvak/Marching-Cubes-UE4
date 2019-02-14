// Fill out your copyright notice in the Description page of Project Settings.

#include "BAir.h"

BAir::BAir()
{
}

BAir::~BAir()
{
}

int8 BAir::IsSolid() const
{
	return -1;
}

FLinearColor BAir::GetVertexColor() const
{
	return FLinearColor(FColor(0, 0, 0));
}