#pragma once

#include "stdafx.h"

class ChunkMapper {
private:

	glm::vec2 mapToMultiple(int x, int y);

	std::list<TerrainChunk>* terrainListRef;

public:

	bool getOpenChunk(glm::vec3 charPos, glm::vec3& outPos);

	bool examineChunk(glm::vec3 charPos, glm::vec3& outPos, int x, int z);

	void setListRef(std::list<TerrainChunk>* tlr);

	ChunkMapper();
	~ChunkMapper();
};