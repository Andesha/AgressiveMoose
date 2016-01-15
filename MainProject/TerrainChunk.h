#pragma once
#include "stdafx.h"
#include "TextureFactory.h"
#include "Perlin.h"
#include "Vertex.h"


/// <summary>
/// Object which will build and then store all of the information to draw itself to screen.
/// Chunk class that will only ever be called with new as few times as possible.
/// The idea is to avoid new's and just rebase chunks.
/// </summary>
class TerrainChunk {
private:

	/// OpenGL buffer storage.
	GLuint vboID;
	GLuint eboID;
	GLuint vaoID;

	/// <summary>
	/// Method for computing all of the vertex normals for a chunk.
	/// Perfectly takes care of edge cases.
	/// </summary>
	/// <param name="pos">Vertex we are currently at.</param>
	/// <returns>Normal vector of the vertex.</return>
	glm::vec3 calcVertexNormal(Position pos, float cX, float cY, Perlin* perlin);

public:

	/// <summary>
	/// Empty default constructor.
	/// </summary>
	TerrainChunk();

	/// <summary>
	/// Implemented but never used destructor.
	/// </summary>
	~TerrainChunk();

	/// <summary>
	/// First time run which will build the chunk for drawing to the screen.
	/// </summary>
	/// <param name="cX">Center X to store.</param>
	/// <param name="cY">Center X to store.</param>
	void initialize(float cX, float cY, Perlin* perlin);

	/// <summary>
	/// Call this instead of deleting and making a new chunk. Will completely recompute all values.
	/// </summary>
	/// <param name="cX">Center X to store.</param>
	/// <param name="cY">Center Y to store.</param>
	void rebase(float cX, float cY, Perlin* perlin); // Takes the chunk and recomputes all values.

	/// <summary>
	/// To be called inside of the game loop. Best used with the "basicShaders" we made.
	/// Will be affected by lighting.
	/// </summary>
	void draw() const;
};

