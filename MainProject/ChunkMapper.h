#pragma once

#include "stdafx.h"

class ChunkMapper {
private:

	glm::vec2 mapToMultiple(int x, int y);

	std::list<TerrainChunk>* terrainListRef;

public:

	glm::vec3 getOpenChunk(glm::vec3 charPos);

	void setListRef(std::list<TerrainChunk>* tlr);

	ChunkMapper();
	~ChunkMapper();
};

int chunkMapHelper[] = { // Mapper which contains the offset of chunks that should be visible relative to the player.
	-8, 8,
	 0, 8, // Top row
	 8, 8
	-8, 0,
	 0, 0, // Middle check first.
	 8, 0
	-8,-8,
	 0,-8, // Middle check first.
	 8,-8
}