#include "stdafx.h"
#include "ChunkMapper.h"


ChunkMapper::ChunkMapper() {
}


ChunkMapper::~ChunkMapper() {
}

glm::vec2 ChunkMapper::mapToMultiple(int x, int y) {
	return glm::vec2(((x - 1) | 7) + 1, ((y - 1) | 7) + 1); // Cute way of mapping the input values. Bit level haxx.
}

void ChunkMapper::setListRef(std::list<TerrainChunk>* tlr) {
	this->terrainListRef = tlr;
}

bool ChunkMapper::examineChunk(glm::vec3 charPos, glm::vec3& outPos, int x, int z) {
	glm::vec2 mappedPos = mapToMultiple((int)(charPos.x / SCALING_FACTOR) + (x * 8), (charPos.z / SCALING_FACTOR) + (z * 8));
	// Scaling of above is done by first rounding to int - scaling down from world space - then doing an offset by the params.

	for (TerrainChunk& tc : *terrainListRef) { // Check over list... 
		if (tc.isDrawing()) { // for chunks that are drawing...
			if (glm::vec2(tc.getCenterX(), tc.getCenterY()) == mappedPos) {
				// If the list contains a chunk at the proper location - return false.
				return false;
			}
		}
	}
	// If we have made it to here it is because there is no chunk at the input location.
	outPos = glm::vec3(mappedPos.x , 0, mappedPos.y); // Write out.
	return true; // Signal we found an open spot.
}

bool ChunkMapper::getOpenChunk(glm::vec3 charPos, glm::vec3& outPos) {
	for (int i = 5; i >= -5; --i) { // These two nested for loops contain the open
		for (int j = -5; j <= 5; ++j) { // area for the class to check for chunks.
			if (examineChunk(charPos, outPos, j, i)) return true; // Found one - quick return.
		}
	}
	// Below return indicated none found.
	return false;
}