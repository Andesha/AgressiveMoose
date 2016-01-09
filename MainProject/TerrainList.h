#pragma once

#include "stdafx.h"
#include "Perlin.h"
#include "TerrainChunk.h"
#include "Character.h"

class TerrainList {

private:

	std::list<TerrainChunk> terrainList;
	Perlin perlin;
	Character* character;

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