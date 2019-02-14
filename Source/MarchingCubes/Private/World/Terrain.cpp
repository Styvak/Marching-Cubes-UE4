// Fill out your copyright notice in the Description page of Project Settings.

#include "Terrain.h"

#include "Engine/World.h"
#include "Components/SceneComponent.h"

#include "Chunk.h"
#include "BlockManager.h"
#include "IBlock.h"

// Sets default values
ATerrain::ATerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = SceneComponent;
}

// Called when the game starts or when spawned
void ATerrain::BeginPlay()
{
	Super::BeginPlay();
	
	Generator = new BiomeGenerator(WorldSettings.Seed);
	for (int x = -WorldSettings.SideChunks / 2; x < WorldSettings.SideChunks / 2; x++) {
		for (int y = -WorldSettings.SideChunks / 2; y < WorldSettings.SideChunks / 2; y++) {
			for (int z = 0; z < WorldSettings.HeightChunks; z++) {
				FIntVector chunkPos(x, y, z);
				FVector pos(x * LOD.SideSize, y * LOD.SideSize, z * LOD.HeightSize);

				Chunks.Add(chunkPos, GetWorld()->SpawnActor<AChunk>(pos, FRotator::ZeroRotator));
				Chunks[chunkPos]->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
				Chunks[chunkPos]->Initialize(LOD.SideDivision, LOD.HeightDivision, LOD.SideSize, LOD.HeightSize, this, chunkPos, Material, Generator);
				Chunks[chunkPos]->GeneratePerlin(WorldSettings.HeightChunks * LOD.HeightDivision);
			}
		}
	}

	for (int x = -WorldSettings.SideChunks / 2; x < WorldSettings.SideChunks / 2; x++) {
		for (int y = -WorldSettings.SideChunks / 2; y < WorldSettings.SideChunks / 2; y++) {
			for (int z = 0; z < WorldSettings.HeightChunks; z++) {
				FIntVector chunkPos(x, y, z);

				Chunks[chunkPos]->GenerateMesh(0.f);
			}
		}
	}
}

// Called every frame
void ATerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

const IBlock *ATerrain::GetPointDivision(uint8 xDiv, uint8 yDiv, uint8 zDiv, FIntVector ChunkPosition) const
{
	while (xDiv < 0)
	{
		xDiv += LOD.SideDivision;
		ChunkPosition.X -= 1;
	}
	while (xDiv >= LOD.SideDivision)
	{
		xDiv -= LOD.SideDivision;
		ChunkPosition.X += 1;
	}
	while (yDiv < 0)
	{
		yDiv += LOD.SideDivision;
		ChunkPosition.Y -= 1;
	}
	while (yDiv >= LOD.SideDivision)
	{
		yDiv -= LOD.SideDivision;
		ChunkPosition.Y += 1;
	}
	while (zDiv < 0)
	{
		zDiv += LOD.HeightDivision;
		ChunkPosition.Z -= 1;
	}
	while (zDiv >= LOD.HeightDivision)
	{
		zDiv -= LOD.HeightDivision;
		ChunkPosition.Z += 1;
	}
	if (ChunkPosition.Z < 0 || ChunkPosition.Z >= WorldSettings.HeightChunks)
		return BlockManager::GetInstance()->GetBlock(BlockID::AIR);
	if (zDiv == LOD.HeightDivision - 1 && ChunkPosition.Z == WorldSettings.HeightChunks - 1)
		return BlockManager::GetInstance()->GetBlock(BlockID::AIR);
	if (Chunks.Contains(ChunkPosition))
		return Chunks[ChunkPosition]->GetPointDivision(xDiv, yDiv, zDiv);
	return BlockManager::GetInstance()->GetBlock(BlockID::AIR);
}