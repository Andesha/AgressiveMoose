#pragma once

#include "stdafx.h"
#include "Perlin.h"
#include "TerrainChunk.h"
#include "Character.h"
#include "ChunkMapper.h"

/// <summary>
/// This class is to store a list of TerrainChunk's and control when to rebase them.
/// As such this class also controls view distance and has references to the Character.
/// </summary>
class TerrainList {

private:

	/// Actual list of chunks.
	std::list<TerrainChunk> terrainList;

	/// Perlin object for examining.
	Perlin perlin;

	/// Reference to our character for getting the position.
	Character* character;

	/// Reference to the ChunkMapper for finding open chunks to draw in.
	ChunkMapper* chunkMapper;

public:

	void setChar(Character* c);

	void examineChunks();

	int chunkCount;

	std::list<TerrainChunk> getList();

	TerrainList(const Perlin& p = Perlin());
	~TerrainList();

	void buildPool(int chunkCount);

	void firstInit();

};