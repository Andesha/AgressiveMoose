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
	float gridIncrement = GRID_WIDTH-1; // Yay for scaling things.
	float rowCounter = CHUNK_PER_ROW-1;

	float countX = 0;
	float countY = 0;
	
	for (TerrainChunk& tc : terrainList) {
		tc.initialize(-gridIncrement + (countX * gridIncrement), gridIncrement + (countY * gridIncrement));

		countX++;
		if (countX > rowCounter) { // Hard coded for now - eventually make a consant as part of the Constants.h
			countX = 0;
			countY++;
		}
	}
}