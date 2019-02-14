// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KismetProceduralMeshLibrary.h"
#include "ChunkMesh.generated.h"

/**
 * 
 */
USTRUCT()
struct FChunkMesh
{
	GENERATED_USTRUCT_BODY()
public:
	FChunkMesh() = default;
	~FChunkMesh() = default;

	TArray<FVector> Vertices;
	TArray<int32> TriangleIndices;
	TArray<FVector2D> TexCoords;
	TArray<FVector> Normals;
	TArray<FProcMeshTangent> Tangents;
	TArray<FLinearColor> VertexColors;
	int TriangleIndex;
	int VertexIndex;
};