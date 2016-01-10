#include "stdafx.h"
#include "TerrainList.h"


TerrainList::TerrainList(const Perlin& p) {
    this->perlin = p;
	nullVec = glm::vec3(0.0f);
	chunkMapper = new ChunkMapper();
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
	for (TerrainChunk& tc : terrainList) {
		float dist = glm::distance(glm::vec2(character->getPos().x, character->getPos().z), glm::vec2(tc.getCenterX()*SCALING_FACTOR, tc.getCenterY()*SCALING_FACTOR));
		if (dist > DISTANCE_CONSTANT) { // Too far away now. Must somehow rebase the chunks.
			tc.drawing = false; // No need to draw it anymore.
			
			// Do a check for possible areas for new chunks to be rebased to.
			// If a possible point exists - say to the left of the player - put the most recently non-drawn chunk there.
			glm::vec3 possiblePos = chunkMapper->getOpenChunk(character->getPos());
			if (possiblePos != nullVec) {
				tc.rebase(possiblePos.x,possiblePos.z);
			}
		}
	}
}