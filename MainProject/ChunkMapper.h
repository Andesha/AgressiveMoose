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