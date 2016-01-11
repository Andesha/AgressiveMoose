#pragma once

#include "stdafx.h"
/// <summary>
/// The responsibility of this class is to determine if there are any chunks for the game to draw to.
/// This class is understood to be made a member of a TerrainList.
/// </summary>
class ChunkMapper {
private:

	/// <summary>
	/// Fancy quick method of taking two numbers and setting them to their nearest multiple of 8.
	/// </summary>
	/// <param name="x">X param to map.</param>
	/// <param name="y">y param to map.</param>
	/// <returns>Returns a vec2 mapped to the closest multiple of 8.</return>
	glm::vec2 mapToMultiple(int x, int y);

	/// Reference to the terrainList that will hold all of our chunks.
	/// Idea is to have this reference so that no copying of any sort needs to be done.
	std::list<TerrainChunk>* terrainListRef;

public:

	/// <summary>
	/// Method which will determine if there is an open chunk or not.
	/// Will return false if there are none.
	/// Upon true - outPos will contain the proper vector to translate to.
	/// </summary>
	/// <param name="charPos">Current character position to examine.</param>
	/// <param name="outPos">C Style multiple return in the form of a reference to a vec3</param>
	/// <returns>Boolean if there is an open chunk. If there was - outPos contains it.</return>
	bool getOpenChunk(glm::vec3 charPos, glm::vec3& outPos);

	/// <summary>
	/// Method which will determine if there is an open chunk or not at a special location.
	/// Will return false if there was not one.
	/// Upon true - outPos will contain the proper vector to translate to.
	/// </summary>
	/// <param name="charPos">Current character position to examine.</param>
	/// <param name="outPos">C Style multiple return in the form of a reference to a vec3</param>
	/// <param name="x">Modifier in x for char relative to chunk.</param>
	/// <param name="z">Modifier in z for char relative to chunk.</param>
	/// <returns>Boolean if there is an open chunk. If there was - outPos contains it.</return>
	bool examineChunk(glm::vec3 charPos, glm::vec3& outPos, int x, int z);

	/// <summary>
	/// To be called as soon as possible by the outside class.
	/// </summary>
	/// <param name="tlr">Reference to the list that contains all of the chunks.</param>
	void setListRef(std::list<TerrainChunk>* tlr);

	/// <summary>
	/// Empty default constructor.
	/// </summary>
	ChunkMapper();

	/// <summary>
	/// Empty default destructor.
	/// </summary>
	~ChunkMapper();
};