#include "stdafx.h"
#include "TerrainList.h"


TerrainList::TerrainList(const Perlin& p) {
    this->perlin = p;
}


TerrainList::~TerrainList() {
}

void TerrainList::setChar(Character* c) {
	character = c;
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
    float gridIncrement = GRID_WIDTH - 1; // Yay for scaling things.
    float rowCounter = CHUNK_PER_ROW - 1;

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

void TerrainList::examineChunks() {
	TerrainChunk& tc = terrainList.front();
	tc.drawing = false;
	std::cout << tc.getCenterX() << "," << tc.getCenterY() << std::endl;
	std::cout << character->getPos().x / SCALING_FACTOR << "," << character->getPos().z / SCALING_FACTOR << std::endl;
}