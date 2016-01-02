#pragma once

#include "stdafx.h"
#include "Perlin.h"
#include "TerrainChunk.h"

class TerrainList {

private:

	std::list<TerrainChunk> terrainList;
	Perlin perlin;

public:

	int chunkCount;

	std::list<TerrainChunk> getList();

	TerrainList(const Perlin& p = Perlin());
	~TerrainList();

	void buildPool(int chunkCount);

	void firstInit();

};