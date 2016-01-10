#include "stdafx.h"
#include "ChunkMapper.h"


ChunkMapper::ChunkMapper() {
}


ChunkMapper::~ChunkMapper() {
}

glm::vec2 ChunkMapper::mapToMultiple(int x, int y) {
	return glm::vec2(((x - 1) | 7) + 1, ((y - 1) | 7) + 1); // Null vector to pass back.
}

void ChunkMapper::setListRef(std::list<TerrainChunk>* tlr) {
	this->terrainListRef = tlr;
}

glm::vec3 ChunkMapper::getOpenChunk(glm::vec3 charPos) {

	glm::vec2 mappedPos = mapToMultiple((int)(charPos.x / SCALING_FACTOR), (charPos.z / SCALING_FACTOR));

	for (TerrainChunk& tc : *terrainListRef) { // Check all of the chunks that are actually drawing for the pos below the char.
		if (tc.isDrawing()) {
			if (glm::vec2(tc.getCenterX(), tc.getCenterY()) == mappedPos) {
				return glm::vec3(0.0f);
			}
		}
	}

	return glm::vec3(mappedPos.x, 0, mappedPos.y);
}