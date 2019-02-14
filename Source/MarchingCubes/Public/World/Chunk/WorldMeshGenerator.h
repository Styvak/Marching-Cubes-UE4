// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Contouring3D.h"
#include "Terrain.h"
#include "ChunkMesh.h"
#include "IBlock.h"

/**
 * 
 */
class WorldMeshGenerator
{
public:
	static void FillMesh(const IBlock ****datas, int size, int height, float surfaceCrossValue, int chunkDivision, int heightDivision, FChunkMesh &Mesh, const ATerrain *Terrain, const FIntVector &ChunkPosition) {
		FVector interpolatedValues[12];
		//for (int i = 0; i < Meshes.Num(); i++)
		Mesh.VertexIndex = 0;

		float cubeSize = size / (float)chunkDivision;
		float heightRatio = height / (float)heightDivision;

		for (int xDiv = 0; xDiv < chunkDivision; xDiv++) {
			float x = xDiv * cubeSize;
			for (int yDiv = 0; yDiv < chunkDivision; yDiv++) {
				float y = yDiv * cubeSize;
				for (int zDiv = 0; zDiv < heightDivision; zDiv++)
				{
					float z = zDiv * heightRatio;

					/*if (Mesh.Vertices.Num() > 64000) {
						UE_LOG(LogTemp, Warning, TEXT("Too many vertices."));
						break;
					}*/

					const IBlock *blocks[8];

					blocks[0] = Terrain->GetPointDivision(xDiv, yDiv, zDiv, ChunkPosition);
					int8 p0 = blocks[0]->IsSolid();
					blocks[1] = Terrain->GetPointDivision(xDiv + 1, yDiv, zDiv, ChunkPosition);
					int8 p1 = blocks[1]->IsSolid();// .Key == nullptr ? 0 : blocks[1].Value;
					blocks[2] = Terrain->GetPointDivision(xDiv, yDiv, zDiv + 1, ChunkPosition);
					int8 p2 = blocks[2]->IsSolid();// .Key == nullptr ? 0 : blocks[2].Value;
					blocks[3] = Terrain->GetPointDivision(xDiv + 1, yDiv, zDiv + 1, ChunkPosition);
					int8 p3 = blocks[3]->IsSolid();// .Key == nullptr ? 0 : blocks[3].Value;
					blocks[4] = Terrain->GetPointDivision(xDiv, yDiv + 1, zDiv, ChunkPosition);
					int8 p4 = blocks[4]->IsSolid();// .Key == nullptr ? 0 : blocks[4].Value;
					blocks[5] = Terrain->GetPointDivision(xDiv + 1, yDiv + 1, zDiv, ChunkPosition);
					int8 p5 = blocks[5]->IsSolid();// .Key == nullptr ? 0 : blocks[5].Value;
					blocks[6] = Terrain->GetPointDivision(xDiv, yDiv + 1, zDiv + 1, ChunkPosition);
					int8 p6 = blocks[6]->IsSolid();// .Key == nullptr ? 0 : blocks[6].Value;
					blocks[7] = Terrain->GetPointDivision(xDiv + 1, yDiv + 1, zDiv + 1, ChunkPosition);
					int8 p7 = blocks[7]->IsSolid();// .Key == nullptr ? 0 : blocks[7].Value;

					//A bitmap indicating which edges the surface of the volume crosses
					int crossBitMap = 0;
					const IBlock *colorBlock = nullptr;

					if (p0 < surfaceCrossValue) crossBitMap |= 1; else if (colorBlock == nullptr && p0 > 0) colorBlock = blocks[0];
					if (p1 < surfaceCrossValue) crossBitMap |= 2; else if (colorBlock == nullptr && p1 > 0) colorBlock = blocks[1];

					if (p2 < surfaceCrossValue) crossBitMap |= 8; else if (colorBlock == nullptr && p2 > 0) colorBlock = blocks[2];
					if (p3 < surfaceCrossValue) crossBitMap |= 4; else if (colorBlock == nullptr && p3 > 0) colorBlock = blocks[3];

					if (p4 < surfaceCrossValue) crossBitMap |= 16; else if (colorBlock == nullptr && p4 > 0) colorBlock = blocks[4];
					if (p5 < surfaceCrossValue) crossBitMap |= 32; else if (colorBlock == nullptr && p5 > 0) colorBlock = blocks[5];

					if (p6 < surfaceCrossValue) crossBitMap |= 128; else if (colorBlock == nullptr && p6 > 0) colorBlock = blocks[6];
					if (p7 < surfaceCrossValue) crossBitMap |= 64; else if (colorBlock == nullptr && p7 > 0) colorBlock = blocks[7];

					//Use the edge look up table to determine the configuration of edges
					int edgeBits = Contouring3D::EdgeTableLookup[crossBitMap];

					//The surface did not cross any edges, this cube is either complelety inside, or completely outside the volume
					if (edgeBits == 0)
						continue;

					float interpolatedCrossingPoint = 0;

					//Calculate the interpolated positions for each edge that has a crossing value

					//Bottom four edges
					if ((edgeBits & 1) > 0)
					{
						interpolatedCrossingPoint = (surfaceCrossValue - p0) / (p1 - p0);
						interpolatedValues[0] = FMath::Lerp(FVector(x, y, z), FVector(x + cubeSize, y, z), interpolatedCrossingPoint);
					}
					if ((edgeBits & 2) > 0)
					{
						interpolatedCrossingPoint = (surfaceCrossValue - p1) / (p3 - p1);
						interpolatedValues[1] = FMath::Lerp(FVector(x + cubeSize, y, z), FVector(x + cubeSize, y, z + heightRatio), interpolatedCrossingPoint);
					}
					if ((edgeBits & 4) > 0)
					{
						interpolatedCrossingPoint = (surfaceCrossValue - p2) / (p3 - p2);
						interpolatedValues[2] = FMath::Lerp(FVector(x, y, z + heightRatio), FVector(x + cubeSize, y, z + heightRatio), interpolatedCrossingPoint);
					}
					if ((edgeBits & 8) > 0)
					{
						interpolatedCrossingPoint = (surfaceCrossValue - p0) / (p2 - p0);
						interpolatedValues[3] = FMath::Lerp(FVector(x, y, z), FVector(x, y, z + heightRatio), interpolatedCrossingPoint);
					}

					//Top four edges
					if ((edgeBits & 16) > 0)
					{
						interpolatedCrossingPoint = (surfaceCrossValue - p4) / (p5 - p4);
						interpolatedValues[4] = FMath::Lerp(FVector(x, y + cubeSize, z), FVector(x + cubeSize, y + cubeSize, z), interpolatedCrossingPoint);
					}
					if ((edgeBits & 32) > 0)
					{
						interpolatedCrossingPoint = (surfaceCrossValue - p5) / (p7 - p5);
						interpolatedValues[5] = FMath::Lerp(FVector(x + cubeSize, y + cubeSize, z), FVector(x + cubeSize, y + cubeSize, z + heightRatio), interpolatedCrossingPoint);
					}
					if ((edgeBits & 64) > 0)
					{
						interpolatedCrossingPoint = (surfaceCrossValue - p6) / (p7 - p6);
						interpolatedValues[6] = FMath::Lerp(FVector(x, y + cubeSize, z + heightRatio), FVector(x + cubeSize, y + cubeSize, z + heightRatio), interpolatedCrossingPoint);
					}
					if ((edgeBits & 128) > 0)
					{
						interpolatedCrossingPoint = (surfaceCrossValue - p4) / (p6 - p4);
						interpolatedValues[7] = FMath::Lerp(FVector(x, y + cubeSize, z), FVector(x, y + cubeSize, z + heightRatio), interpolatedCrossingPoint);
					}

					//Side four edges
					if ((edgeBits & 256) > 0)
					{
						interpolatedCrossingPoint = (surfaceCrossValue - p0) / (p4 - p0);
						interpolatedValues[8] = FMath::Lerp(FVector(x, y, z), FVector(x, y + cubeSize, z), interpolatedCrossingPoint);
					}
					if ((edgeBits & 512) > 0)
					{
						interpolatedCrossingPoint = (surfaceCrossValue - p1) / (p5 - p1);
						interpolatedValues[9] = FMath::Lerp(FVector(x + cubeSize, y, z), FVector(x + cubeSize, y + cubeSize, z), interpolatedCrossingPoint);
					}
					if ((edgeBits & 1024) > 0)
					{
						interpolatedCrossingPoint = (surfaceCrossValue - p3) / (p7 - p3);
						interpolatedValues[10] = FMath::Lerp(FVector(x + cubeSize, y, z + heightRatio), FVector(x + cubeSize, y + cubeSize, z + heightRatio), interpolatedCrossingPoint);
					}
					if ((edgeBits & 2048) > 0)
					{
						interpolatedCrossingPoint = (surfaceCrossValue - p2) / (p6 - p2);
						interpolatedValues[11] = FMath::Lerp(FVector(x, y, z + heightRatio), FVector(x, y + cubeSize, z + heightRatio), interpolatedCrossingPoint);
					}

					//Shift the cross bit map to use as an index into the triangle look up table
					crossBitMap <<= 4;

					Mesh.TriangleIndex = 0;
					while (Contouring3D::TriangleLookupTable[crossBitMap + Mesh.TriangleIndex] != -1)
					{
						//(Radius + Z) * xyz
						//For each triangle in the look up table, create a triangle and add it to the list.
						int index1 = Contouring3D::TriangleLookupTable[crossBitMap + Mesh.TriangleIndex];
						int index2 = Contouring3D::TriangleLookupTable[crossBitMap + Mesh.TriangleIndex + 1];
						int index3 = Contouring3D::TriangleLookupTable[crossBitMap + Mesh.TriangleIndex + 2];

						FVector vec1(interpolatedValues[index1].X, interpolatedValues[index1].Y, interpolatedValues[index1].Z);
						Mesh.Vertices.Add(vec1);
						FVector vec2(interpolatedValues[index2].X, interpolatedValues[index2].Y, interpolatedValues[index2].Z);
						Mesh.Vertices.Add(vec2);
						FVector vec3(interpolatedValues[index3].X, interpolatedValues[index3].Y, interpolatedValues[index3].Z);
						Mesh.Vertices.Add(vec3);

						/*
						** Calculate the normals
						*/
						FVector n = FVector::CrossProduct(vec3 - vec1, vec2 - vec1).GetSafeNormal();

						Mesh.Normals.Add(n);
						Mesh.Normals.Add(n);
						Mesh.Normals.Add(n);

						Mesh.TriangleIndices.Add(Mesh.VertexIndex);
						Mesh.TriangleIndices.Add(Mesh.VertexIndex + 1);
						Mesh.TriangleIndices.Add(Mesh.VertexIndex + 2);

						/*	for (int i = 0; i < 8; i++)
								if (blocks[i].Key && blocks[i].Key->GetId() != 14) {
									Meshes[0].VertexColors.Add(FLinearColor(blocks[i].Key->GetColor()));
									Meshes[0].VertexColors.Add(FLinearColor(blocks[i].Key->GetColor()));
									Meshes[0].VertexColors.Add(FLinearColor(blocks[i].Key->GetColor()));
									break;
								}*/
						Mesh.VertexColors.Add(colorBlock->GetVertexColor());
						Mesh.VertexColors.Add(colorBlock->GetVertexColor());
						Mesh.VertexColors.Add(colorBlock->GetVertexColor());
						Mesh.VertexIndex += 3;
						Mesh.TriangleIndex += 3;
					}
				}
			}
		}

		//Create texture coordinates for all the vertices
		FVector2D emptyTexCoords0(0, 0);
		FVector2D emptyTexCoords1(0, 100);
		FVector2D emptyTexCoords2(100, 100);

		//for (int texturePointer = 0; texturePointer < Meshes[block0->GetId()].Vertices.Num(); texturePointer += 3) {
		//	//There should be as many texture coordinates as vertices.
		//	//This example does not support textures, so fill with zeros
		//	Meshes[block0->GetId()].TexCoords.Add(emptyTexCoords1);
		//	Meshes[block0->GetId()].TexCoords.Add(emptyTexCoords2);
		//	Meshes[block0->GetId()].TexCoords.Add(emptyTexCoords0);
		//}

		//TArray<FVector> normals;
		//TArray<FProcMeshTangent> tangents;
		//TArray<FLinearColor> vertexColors;

		//mesh->ClearAllMeshSections();

		//mesh->CreateMeshSection_LinearColor(0, vertices, triangleIndices, normals, texCoords, vertexColors, tangents, true);
		//mesh->ContainsPhysicsTriMeshData(true);
	}
};
