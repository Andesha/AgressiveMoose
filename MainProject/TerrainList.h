#pragma once

#include "stdafx.h"
#include "Perlin.h"
#include "TerrainChunk.h"
#include "Character.h"
#include "ChunkMapper.h"

class TerrainList {

private:

	std::list<TerrainChunk> terrainList;
	Perlin perlin;
	Character* character;
	ChunkMapper* chunkMapper;
	glm::vec3 nullVec;

public:

	void setChar(Character* c);

	void examineChunks();

	int chunkCount;

	std::list<TerrainChunk> getList();

	TerrainList(const Perlin& p = Perlin());
	~TerrainList();

	void buildPool(int chunkCount);

	void firstInit();

};