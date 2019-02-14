// Fill out your copyright notice in the Description page of Project Settings.

#include "Chunk.h"

#include "Components/SceneComponent.h"
#include "ProceduralMeshComponent.h"

#include "ChunkMesh.h"
#include "WorldMeshGenerator.h"
#include "FastNoise.h"
#include "BlockManager.h"

// Sets default values
AChunk::AChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = SceneComponent;

	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Mesh"));
	Mesh->bUseAsyncCooking = true;
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

AChunk::~AChunk()
{
	if (Data)
	{
		for (uint16 x = 0; x < SideDivision; x++) {
			for (uint16 y = 0; y < SideDivision; y++) {
				delete Data[x][y];
			}
			delete Data[x];
		}
		delete Data;
	}
}

void AChunk::Initialize(uint16 SideDivision, uint16 HeightDivision, uint16 SideSize, uint16 HeightSize, const ATerrain *Terrain, const FIntVector &ChunkPosition, UMaterialInterface *Material, const BiomeGenerator *Generator)
{
	this->SideDivision = SideDivision;
	this->HeightDivision = HeightDivision;
	this->SideSize = SideSize;
	this->HeightSize = HeightSize;
	this->Terrain = Terrain;
	this->ChunkPosition = ChunkPosition;
	this->Material = Material;
	this->Generator = Generator;

	Data = new const IBlock ***[SideDivision];
	for (uint16 x = 0; x < SideDivision; x++) {
		Data[x] = new const IBlock **[SideDivision];
		for (uint16 y = 0; y < SideDivision; y++) {
			Data[x][y] = new const IBlock *[HeightDivision];
			memset(Data[x][y], 0, sizeof(const IBlock *) * HeightDivision);
		}
	}
}

void AChunk::GenerateMesh(float surfaceCrossValue)
{
	FChunkMesh FMesh;

	WorldMeshGenerator::FillMesh(Data, SideSize, HeightSize, surfaceCrossValue, SideDivision, HeightDivision, FMesh, Terrain, ChunkPosition);

	Mesh->ClearAllMeshSections();

	Mesh->CreateMeshSection_LinearColor(0, FMesh.Vertices, FMesh.TriangleIndices, FMesh.Normals, FMesh.TexCoords, FMesh.VertexColors, FMesh.Tangents, true);
	Mesh->ContainsPhysicsTriMeshData(true);
	Mesh->SetMaterial(0, Material);
}

void AChunk::GeneratePerlin(unsigned int MaxHeight)
{
	float chunkPosX = ChunkPosition.X * SideSize;
	float chunkPosY = ChunkPosition.Y * SideSize;
	unsigned int baseHeight = ChunkPosition.Z * HeightDivision;
	float sideScale = SideSize / (float)SideDivision;

	for (uint8 x = 0; x < SideDivision; x++) {
		for (uint8 y = 0; y < SideDivision; y++) {
			float xPos = chunkPosX + x * sideScale;
			float yPos = chunkPosY + y * sideScale;

			FVector pos(xPos, yPos, 0.f);
			Generator->FillColumn(pos, Data[x][y], baseHeight, HeightDivision, MaxHeight, HeightSize);
		}
	}
	//FastNoise noise;
	//noise.SetSeed(1337);
	////noise.SetFrequency(0.02f);
	//noise.SetNoiseType(FastNoise::Simplex);
	//noise.SetFractalType(FastNoise::FBM);
	////noise.SetFractalOctaves(45);

	//float heightScale = HeightSize / (float)HeightDivision;
	//float sideScale = SideSize / (float)SideDivision;

	//float chunkPosX = ChunkPosition.X * SideSize;
	//float chunkPosY = ChunkPosition.Y * SideSize;
	//float chunkPosZ = ChunkPosition.Z * HeightSize;

	//for (uint8 x = 0; x < SideDivision; x++) {
	//	for (uint8 y = 0; y < SideDivision; y++) {
	//		for (uint8 z = 0; z < HeightDivision; z++) {
	//			float xPos = chunkPosX + x * sideScale;
	//			float yPos = chunkPosY + y * sideScale;
	//			float zPos = chunkPosZ + z * heightScale;
	//			xPos /= 20.f;
	//			yPos /= 20.f;
	//			zPos /= 20.f;
	//			float val = noise.GetNoise(zPos, xPos + yPos) - noise.GetNoise(xPos, yPos);
	//			val -= (((float)zPos / HeightDivision) - 0.5f);
	//			Data[x][y][z] = val > 0 ? BlockManager::GetInstance()->GetBlock(BlockID::STONE) : BlockManager::GetInstance()->GetBlock(BlockID::AIR);
	//		}
	//	}
	//}
}

const IBlock *AChunk::GetPointDivision(uint8 xDiv, uint8 yDiv, uint8 zDiv) const
{
	if (zDiv == 0 && ChunkPosition.Z == 0)
		return BlockManager::GetInstance()->GetBlock(BlockID::STONE);
	return Data[xDiv][yDiv][zDiv];
}
