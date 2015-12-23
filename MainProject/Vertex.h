#pragma once
#include "stdafx.h"

// Reusable struct for storing x,y,z positions.
struct Position {
	float x;
	float y;
	float z;
};

// Reusable struct for displaying colour.
struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

// Vertex struct for passing into the GPU.
struct Vertex {
	Position position;
	Color color;
};