#include "stdafx.h"
#include "TerrainList.h"


TerrainList::TerrainList(const Perlin& p) {
    this->perlin = p;
	chunkMapper = new ChunkMapper();
	chunkMapper->setListRef(&terrainList);
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

	// Note that this only builds and does not initialize.
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
		float xTrans = -gridIncrement + (countX * gridIncrement);
		float zTrans = -gridIncrement + (countY * gridIncrement); // Confusing but that's life.

		//std::cout << xTrans << "," << zTrans << std::endl; // Note that this is very much so in world coordinates.

		tc.initialize(xTrans,zTrans);

        countX++;
        if (countX > rowCounter) { // Make the grid of chunks square.
            countX = 0;
            countY++;
        }
    }
}

void TerrainList::examineChunks() {
	for (TerrainChunk& tc : terrainList) { // MAKE THIS NOT JUST REBASE WHEN DEALLOCATING
		if (tc.isDrawing()) { // only do computations if theres a CHANGED.
			float dist = glm::distance(glm::vec2(character->getPos().x, character->getPos().z), glm::vec2(tc.getCenterX()*SCALING_FACTOR, tc.getCenterY()*SCALING_FACTOR));
			if (dist > DISTANCE_CONSTANT) { // View distance.
				tc.drawing = false;
			}
		}

		// Slightly-cheesy-on-purpose-fall-through-if
		if(!tc.isDrawing()) {
			glm::vec3 possiblePos; // Check for open positions to redraw things.
			if (chunkMapper->getOpenChunk(character->getPos(),possiblePos)) {
				tc.rebase(possiblePos.x, possiblePos.z); // If here - rebase at possiblePos.
			}
		}
	}
}