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

	/// Storage for where to translate the chunk to in world space.
	float centerX, centerY;

	/// OpenGL buffer storage.
	GLuint vboID;
	GLuint eboID;

	/// Reference to the perlin object for computation during start and normals.
	Perlin perlin;

	/// <summary>
	/// Method for computing all of the vertex normals for a chunk.
	/// Perfectly takes care of edge cases.
	/// </summary>
	/// <param name="pos">Vertex we are currently at.</param>
	/// <returns>Normal vector of the vertex.</return>
    glm::vec3 calcVertexNormal(Position pos);

public:

	/// <summary>
	/// Empty default constructor.
	/// </summary>
	TerrainChunk();

	/// <summary>
	/// Implemented but never used destructor.
	/// </summary>
	~TerrainChunk();

	/// Storage of if the object is currently drawing to the screen or not.
	bool drawing;

	/// Public vao for outside of class manipulation.
	GLuint vaoID;

	/// <summary>
	/// Send a perlin object to this class to use.
	/// </summary>
	/// <param name="p">Send a perlin object to this class to use.</param>
	void sendPerlin(Perlin& p);

	/// <summary>
	/// Getter for the member variable drawing.
	/// </summary>
	/// <returns>Boolean if the chunk is drawing or not.</return>
	bool isDrawing();

	/// <summary>
	/// Get the value of the x coordinate of the center of the chunk.
	/// </summary>
	/// <returns>Float center of the chunk in x</return>
	float getCenterX();

	/// <summary>
	/// Get the value of the y coordinate of the center of the chunk.
	/// Note that this is technically in Z but named very poorly.
	/// </summary>
	/// <returns>Float center of the chunk in y/z</return>
	float getCenterY();

	/// <summary>
	/// First time run which will build the chunk for drawing to the screen.
	/// </summary>
	/// <param name="cX">Center X to store.</param>
	/// <param name="cY">Center X to store.</param>
	void initialize(float cX, float cY);

	/// <summary>
	/// Call this instead of deleting and making a new chunk. Will completely recompute all values.
	/// </summary>
	/// <param name="cX">Center X to store.</param>
	/// <param name="cY">Center Y to store.</param>
	void rebase(float cX, float cY); // Takes the chunk and recomputes all values.

	/// <summary>
	/// To be called inside of the game loop. Best used with the "basicShaders" we made.
	/// Will be affected by lighting.
	/// </summary>
	void draw();
};

