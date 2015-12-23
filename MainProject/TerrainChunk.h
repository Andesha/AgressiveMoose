#pragma once
#include "stdafx.h"

// Chunk class that will only ever be called with new as few times as possible.
// The idea is to avoid new's and just rebase chunks.
class TerrainChunk {
private:
	bool drawing;
	float centerX, centerY;
	GLuint vboID;
	GLuint eboID;
	GLuint vaoID;

	float examinePerlin(int x, int y); // Examine the perlin system to find out height.

public:
	TerrainChunk();
	~TerrainChunk();

	bool isDrawing();
	float getCenterX();
	float getCenterY();

	void initialize(float cX, float cY);

	void rebase(float cX, float cY); // Takes the chunk and recomputes all values.

	void draw();
};

