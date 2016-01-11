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

bool ChunkMapper::examineChunk(glm::vec3 charPos, glm::vec3& outPos, int x, int z) {
	glm::vec2 mappedPos = mapToMultiple((int)(charPos.x / SCALING_FACTOR) + (x * 8), (charPos.z / SCALING_FACTOR) + (z * 8)); // Char pos to 8's

	for (TerrainChunk& tc : *terrainListRef) { // Check all of the chunks that are actually drawing for the pos below the char.
		if (tc.isDrawing()) {
			if (glm::vec2(tc.getCenterX(), tc.getCenterY()) == mappedPos) {
				return false;
			}
		}
	}
	
	outPos = glm::vec3(mappedPos.x , 0, mappedPos.y);
	return true;
}

bool ChunkMapper::getOpenChunk(glm::vec3 charPos, glm::vec3& outPos) {
	for (int i = 5; i >= -5; --i) {
		for (int j = -5; j <= 5; ++j) {
			if (examineChunk(charPos, outPos, j, i)) return true;
		}
	}
	
	return false;
}