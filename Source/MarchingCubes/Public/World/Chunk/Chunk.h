// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chunk.generated.h"

class ATerrain;
class IBlock;
class USceneComponent;
class UProceduralMeshComponent;
class BiomeGenerator;

UCLASS()
class MARCHINGCUBES_API AChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunk();
	virtual ~AChunk();

public:	
	void Initialize(uint16 SideDivision, uint16 HeightDivision, uint16 SideSize, uint16 HeightSize, const ATerrain *Terrain, const FIntVector &ChunkPosition, UMaterialInterface *Material, const BiomeGenerator *Generator);

	void GenerateMesh(float surfaceCrossValue);
	void GeneratePerlin(unsigned int MaxHeight);

	const IBlock *GetPointDivision(uint8 xDiv, uint8 yDiv, uint8 zDiv) const;

protected:
	UPROPERTY(EditAnywhere)
	USceneComponent *SceneComponent;

	UPROPERTY(EditAnywhere)
	UProceduralMeshComponent *Mesh;

	const IBlock ****Data;

	uint16 SideDivision;
	uint16 HeightDivision;

	uint16 SideSize;
	uint16 HeightSize;

	const ATerrain *Terrain;
	FIntVector ChunkPosition;

	UMaterialInterface *Material;

	const BiomeGenerator *Generator;
};
