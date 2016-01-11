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

	/// Perlin object for pass through.
	Perlin perlin;

	/// Reference to our character for getting the position.
	Character* character;

	/// Reference to the ChunkMapper for finding open chunks to draw in.
	ChunkMapper* chunkMapper;

public:

	/// <summary>
	/// Set the reference to the character we are playing with.
	/// </summary>
	/// <param name="c">Character to use as anchor.</param>
	void setChar(Character* c);

	/// <summary>
	/// Called from the outside game loop.
	/// Function will take care of rebasing and marking chunks for drawing or not.
	/// </summary>
	void examineChunks();

	/// Count of chunks to first build.
	int chunkCount;

	/// <summary>
	/// Return the terrainList that this class is holding.
	/// </summary>
	/// <returns>Standard list of TerrainChunk type</return>
	std::list<TerrainChunk> getList();

	TerrainList(const Perlin& p = Perlin());

	/// <summary>
	/// Default destructor to never really be called.
	/// </summary>
	~TerrainList();

	/// <summary>
	/// Build/allocate a given number of chunks.
	/// </summary>
	/// <param name="chunkCount">Number of chunks to build.</param>
	void buildPool(int chunkCount);

	/// <summary>
	/// Translate the freshly built chunks into their first positions.
	/// </summary>
	void firstInit();

};