#pragma once
#include "stdafx.h"
#include "TextureFactory.h"
#include "Perlin.h"

// Chunk class that will only ever be called with new as few times as possible.
// The idea is to avoid new's and just rebase chunks.
class TerrainChunk {
private:
	
	float centerX, centerY;
	GLuint vboID;
	GLuint eboID;
	Perlin perlin;
	float examinePerlin(float x, float y); // Examine the perlin system to find out height.

public:
	TerrainChunk();
	~TerrainChunk();

	bool drawing;

	GLuint vaoID; // make private again

	void sendPerlin(Perlin& p);

	bool isDrawing();
	float getCenterX();
	float getCenterY();

	void initialize(float cX, float cY);

	void rebase(float cX, float cY); // Takes the chunk and recomputes all values.

	void draw();
};

