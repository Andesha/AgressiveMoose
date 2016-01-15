#pragma once

#include "stdafx.h"
#include "Perlin.h"
#include "TerrainChunk.h"
#include "Character.h"

class ChunkMap;

/// <summary>
/// This class is to store a list of TerrainChunk's and control when to rebase them.
/// As such this class also controls view distance and has references to the Character.
/// </summary>
class TerrainList {

private:
	ChunkMap* chunkMap;

	/// Perlin object for pass through.
	Perlin perlin;

	/// Reference to our character for getting the position.
	Character* character;

	float chunkX, chunkZ;

public:

	struct ChunkRef {
		const TerrainChunk* chunk;
		float centerX;
		float centerY;
	};

	class const_iterator {
	friend class TerrainList;

	public:
		ChunkRef operator*() const;
		bool operator!=(const const_iterator& other) const;
		const_iterator& operator++();

	private:
		const_iterator(int32_t x, int32_t z, const TerrainList* list);
		int32_t x, z;
		const TerrainList* list;
	};

	const_iterator begin() const;
	const_iterator end() const;

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

	TerrainList(const Perlin& p = Perlin());

	/// <summary>
	/// Default destructor to never really be called.
	/// </summary>
	~TerrainList();

	/// <summary>
	/// Translate the freshly built chunks into their first positions.
	/// </summary>
	void firstInit();

};