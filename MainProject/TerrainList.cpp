#include "stdafx.h"
#include "TerrainList.h"


TerrainList::TerrainList(const Perlin& p) {
	this->perlin = p;
}


TerrainList::~TerrainList() {
}

std::list<TerrainChunk> TerrainList::getList() {
	return this->terrainList;
}

void TerrainList::buildPool(int chunkCount) {
	this->chunkCount = chunkCount;

	for (int i = 0; i < chunkCount; i++) {
		TerrainChunk temp = TerrainChunk();
		temp.sendPerlin(perlin);

		terrainList.push_back(temp);
	}
}

void TerrainList::firstInit() {
	float gridWidth = 3-1;

	float countX = 0;
	float countY = 0;
	
	for (TerrainChunk& tc : terrainList) {
		tc.initialize(-gridWidth + (countX * gridWidth), gridWidth + (countY * gridWidth));

		countX++;
		if (countX > gridWidth) {
			countX = 0;
			countY++;
		}
	}
}