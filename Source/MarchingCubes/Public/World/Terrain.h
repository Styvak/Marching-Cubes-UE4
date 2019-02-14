// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BiomeGenerator.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Terrain.generated.h"

class USceneComponent;
class AChunk;
class IBlock;

USTRUCT()
struct FLODLevel {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float Distance;

	UPROPERTY(EditAnywhere)
	uint16 SideSize;

	UPROPERTY(EditAnywhere)
	uint16 HeightSize;

	UPROPERTY(EditAnywhere)
	uint16 SideDivision;

	UPROPERTY(EditAnywhere)
	uint16 HeightDivision;
};

USTRUCT()
struct FTerrainSettings {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	uint8 SideChunks;

	UPROPERTY(EditAnywhere)
	uint8 HeightChunks;

	UPROPERTY(EditAnywhere)
	int Seed;
};

UCLASS()
class MARCHINGCUBES_API ATerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerrain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	const IBlock *GetPointDivision(uint8 xDiv, uint8 yDiv, uint8 zDiv, FIntVector ChunkPosition) const;

protected:
	UPROPERTY(EditAnywhere)
	USceneComponent *SceneComponent;

	UPROPERTY(EditAnywhere)
	FLODLevel LOD;

	UPROPERTY(EditAnywhere)
	FTerrainSettings WorldSettings;

	UPROPERTY(EditAnywhere, Category = "Graphics")
	UMaterialInterface *Material;

	BiomeGenerator *Generator;

	TMap<FIntVector, AChunk *> Chunks;
};
